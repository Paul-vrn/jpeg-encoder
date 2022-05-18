#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


struct huff_table{

    uint8_t *htables_nb_symb_per_lengths;
    uint8_t *htables_symbols;
    uint8_t nb_symbols;
    uint32_t *huffcode_table;

};

struct node
{
    uint8_t used;
    struct node *left;
    struct node *right;
};

struct node *createNode()
{
    struct node *node = calloc(1, sizeof(struct node));
    node->used = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}





bool recursif(struct node *currentNode, uint32_t code, uint32_t depth, uint32_t *huffcode_table, uint32_t *index){
    if(depth==0){
        if(currentNode->used==0){
            currentNode->used = 1;
            huffcode_table[*index] = code;
            (*index)++;
            return 1;
        }
        return 0;
    }
    if (currentNode->used == 1){

        return 0;

    }

    /*Test gauche*/
    if(currentNode->left==NULL){
        currentNode->left = createNode();
    }
    if(recursif(currentNode->left, code<<1, depth-1, huffcode_table, index) == 1){
        return 1;
    }

    /*Test droit*/
    if(currentNode->right==NULL){
        currentNode->right = createNode();
    }
    if(recursif(currentNode->right, (code<<1)+ 1, depth-1, huffcode_table, index) == 1){
        return 1;
    }

    return 0;

}

uint32_t *huffcode_table_build(struct huff_table *hufftable)
{
    uint32_t index = 0;
    uint32_t *huffcode_table = calloc(hufftable->nb_symbols, sizeof(uint32_t));
    struct node *root = createNode();
    for(uint32_t i=0; i<16; i++){
        for(uint32_t j=0; j<hufftable->htables_nb_symb_per_lengths[i]; j++){
            recursif(root, (uint32_t)0, i+1, huffcode_table, &index);
            
        }
    
    }
    return huffcode_table;
}

uint32_t huffman_table_get_path(struct huff_table *ht, uint8_t value, uint8_t *nb_bits){

    for(uint32_t i=0; i<ht->nb_symbols; i++){
        if(ht->htables_symbols[i]==value){
            int32_t k = i;
            uint32_t cpt = 0;
            while(k>=0){
                k -= ht->htables_nb_symb_per_lengths[cpt];
                cpt += 1;
            }
            *nb_bits = cpt;
            return ht->huffcode_table[i];
        }
    }
    return 0;
}


struct huff_table *huffman_table_build(uint8_t *nb_symb_per_lengths, uint8_t *symbols, uint8_t nb_symbols){

    struct huff_table *table = calloc(1, sizeof(struct huff_table));

    table->htables_nb_symb_per_lengths = nb_symb_per_lengths;
    table->htables_symbols = symbols;
    table->nb_symbols = nb_symbols;
    // table->huffcode_table = calloc(nb_symbols, sizeof(uint32_t));
    table->huffcode_table = huffcode_table_build(table);

    return table;

}



uint8_t *huffman_table_get_symbols(struct huff_table *ht){

    return ht->htables_symbols;

}

uint8_t *huffman_table_get_length_vector(struct huff_table *ht){

    return ht->htables_nb_symb_per_lengths;

}

void huffman_table_destroy(struct huff_table *ht){

    free(ht);
}


