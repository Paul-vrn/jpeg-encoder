#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "jpeg_writer.h"
#include "huffman.h"

struct huffman_table
{
    uint8_t *nb_symb_per_lengths;
    uint8_t *symbols;
    uint8_t nb_symbols;
    uint32_t *huffcode_table;
};

struct node
{
    uint8_t used;
    struct node *left;
    struct node *right;
};

struct node *createNode_moi()
{
    struct node *node_ToReturn = calloc(1, sizeof(struct node));
    node_ToReturn->used = 0;
    node_ToReturn->left = NULL;
    node_ToReturn->right = NULL;
    return node_ToReturn;
}

struct huffman_table *huffman_table_build_moi(uint8_t *nb_symb_per_lengths,
                                              uint8_t *symbols,
                                              uint8_t nb_symbols)
{
    struct huff_table *hufftable_ToReturn = calloc(1, sizeof(struct huffman_table));
    huffmantable_ToReturn->nb_symb_per_lengths = nb_symb_per_lengths;
    huffmantable_ToReturn->symbols = symbols;
    huffmantable_ToReturn->nb_symbols = nb_symbols;
    huffmantable_ToReturn->huffcode_table = calloc(nb_symbols, sizeof(uint32_t));
    return hufftable_ToReturn;  
}

bool recursif_moi(struct node *currentNode, uint32_t code, uint32_t depth, uint32_t huffcode_table, uint32_t *index){
    if(depth==0){
        if(currentNode->used==0){
            currentNode->used = 1;
            huffcode_table[index] = code;
            (*index)++;
            return 1;
        }
        return 0;
}
    /*Test gauche*/
    if(currentNode->left==NULL){
        currentNode->left = createNode_moi();
    }
    if(recursif_moi(currentNode->left, code<<1, depth-1, huffcode_table, index)){
        return 1;
    }

    /*Test droit*/
    if(currentNode->right==NULL){
        currentNode->right = createNode_moi();
    }
    if(recursif_moi(currentNode->right, (code<<1)|1, depth-1, huffcode_table, index)){
        return 1;
    }

    return 0;

}

uint32_t huffcode_table_build_moi(struct huffman_table *hufftable)
{
    uint32_t index = 0;
    uint32_t huffcode_table[hufftable->nb_symbols];
    struct node *root = createNode_moi();
    for(uint32_t i=0; i<16; i++){
        for(uint32_t j=0; j<hufftable->nb_symb_per_lengths; j++){
            recursif_moi(root, 0, i+1, huffcode_table, &index)
            
        }
    hufftable->huffcode_table = huffcode_table;
    }
}
uint32_t huffman_table_get_path_moi(struct huffman_table *ht, uint8_t value, uint8_t *nb_bits){
    huffcode_table_build_moi(ht);
    for(uint32_t i=0; i<ht->nb_symbols; i++){
        if(ht->symbols[i]==value){
            *nb_bits = ht->nb_symb_per_lengths[i];
            return ht->huffcode_table[i];
        }
    }
}


uint8_t *huffman_table_get_symbols_moi(struct huffman_table *ht)
{
    return ht->symbols;
}

uint8_t *huffman_table_get_length_vector_moi(struct huffman_table *ht)
{
    return ht->nb_symb_per_lengths;
}

void huffman_table_destroy_moi(struct huffman_table *ht)
{
    free(ht);
}