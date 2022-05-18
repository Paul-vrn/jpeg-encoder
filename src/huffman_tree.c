/**
 * @file huffman_tree.c
 * @author Marc Félix-Henry (marc.felix-henry@grenoble-inp.org)
 * @brief file to create the huffman tree
 * @version 1.0
 * @date 2022-05-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


struct huff_table1{

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


void huffman_table_destroy1(struct huff_table1 *ht){
        free(ht);
}

void tree_destroy(struct node *node)
{
    if (node->left != NULL)
        tree_destroy(node->left);
    if (node->right != NULL)
        tree_destroy(node->right);
    free(node);
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
    /*Test gauche*/
    if(currentNode->left==NULL){
        currentNode->left = createNode();
    }
    if(recursif(currentNode->left, code<<1, depth-1, huffcode_table, index)){
        return 1;
    }

    /*Test droit*/
    if(currentNode->right==NULL){
        currentNode->right = createNode();
    }
    if(recursif(currentNode->right, (code<<1)|1, depth-1, huffcode_table, index)){
        return 1;
    }

    return 0;

}

void huffcode_table_build1(struct huff_table1 *hufftable)
{
    uint32_t index = 0;
    uint32_t huffcode_table[hufftable->nb_symbols];
    struct node *root = createNode();
    for(uint32_t i=0; i<16; i++){
        for(uint32_t j=0; j<hufftable->htables_nb_symb_per_lengths[i]; j++){
            recursif(root, 0, i+1, huffcode_table, &index);
            
        }
    hufftable->huffcode_table = huffcode_table;
    }
    tree_destroy(root);
}

uint32_t huffman_table_get_path1(struct huff_table1 *ht, uint8_t value, uint8_t *nb_bits){
    for(uint32_t i=0; i<ht->nb_symbols; i++){
        if(ht->htables_symbols[i]==value){
            *nb_bits = ht->htables_nb_symb_per_lengths[i];
            return ht->huffcode_table[i];
        }
    }
    return 0;
}


struct huff_table1 *huffman_table_build1(uint8_t *nb_symb_per_lengths, uint8_t *symbols, uint8_t nb_symbols){

    struct huff_table1 *table = calloc(1, sizeof(struct huff_table1));

    table->htables_nb_symb_per_lengths = nb_symb_per_lengths;
    table->htables_symbols = symbols;
    table->nb_symbols = nb_symbols;
    // table->huffcode_table = calloc(nb_symbols, sizeof(uint32_t));
    huffcode_table_build1(table);

    return table;

}



uint8_t *huffman_table_get_symbols1(struct huff_table1 *ht){

    return ht->htables_symbols;

}

uint8_t *huffman_table_get_length_vector1(struct huff_table1 *ht){

    return ht->htables_nb_symb_per_lengths;

}
