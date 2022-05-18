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

/**
 * @brief A struct to store the different usfull informations to build the huffman tree.
 *  The tree is then store in the form of a list.
 * 
 */
struct huff_table{

    uint8_t *htables_nb_symb_per_lengths;
    uint8_t *htables_symbols;
    uint8_t nb_symbols;
    uint32_t *huffcode_table;

};
/**
 * @brief A struct to create the huffman tree that is used
 *  later to get the huffman codes of symbols. 
 */
struct node
{
    uint8_t used;
    struct node *left;
    struct node *right;
};
/**
 * @brief Create a Node object
 * @param none: no parameter, create a new node empty
 * @return struct node* 
 */
struct node *createNode()
{
    struct node *node = calloc(1, sizeof(struct node));
    node->used = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/**
 * @brief Free the memory of all nodes of a tree
 * @param node: the root of the tree
 * @return none
 */
void node_destroy(struct node *node)
{
    if (node->left != NULL)
        node_destroy(node->left);
    if (node->right != NULL)
        node_destroy(node->right);
    free(node);
}

/**
 * @brief Create an tree composed of nodes, the objetive of this fonction
 * is actually to create the uint32_t huffcode_table that is needed.
 * @param currentNode 
 * @param code = huffman code of the current node
 * @param depth = used to know the depth of the tree, the depth is the number of bits used to encode the current node
 * @param huffcode_table 
 * @param index = index of the huffcode_table
 * @return true = 1
 * @return false = 0
 */
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
    if (currentNode->used == 1){   //Le code de Huffman est préfixé, donc pas de fils pour un noeud utilisé

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

/**
 * @brief Create the huffman tree and consequently the huffman code table
 * 
 * @param nb_symb_per_lengths 
 * @param symbols 
 * @param nb_symbols 
 * @return struct huff_table* 
 */
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
    node_destroy(root);
    return huffcode_table;
}

/**
 * @brief When called, return the huffman code of a symbol
 * 
 * @param[in] ht huffman table
 * @param[in] value symbol
 * @param[out] nb_bits number of bits used to encode the symbol
 * @return uint32_t 
 */
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


/**
 * @brief Create the huffman table structure
 * 
 * @param nb_symb_per_lengths length of each symbol
 * @param symbols pointer to the symbols
 * @param nb_symbols number of symbols
 * @return struct huff_table* huffman table
 */
struct huff_table *huffman_table_build(uint8_t *nb_symb_per_lengths, uint8_t *symbols, uint8_t nb_symbols){

    struct huff_table *table = calloc(1, sizeof(struct huff_table));

    table->htables_nb_symb_per_lengths = nb_symb_per_lengths;
    table->htables_symbols = symbols;
    table->nb_symbols = nb_symbols;
    // table->huffcode_table = calloc(nb_symbols, sizeof(uint32_t));
    table->huffcode_table = huffcode_table_build(table);

    return table;

}


/**
 * @brief Return the list of symbols in the huffman tree.
 * 
 * @param ht 
 * @return uint8_t* 
 */
uint8_t *huffman_table_get_symbols(struct huff_table *ht){

    return ht->htables_symbols;

}

/**
 * @brief Return the list of number of symbols per length in the huffman tree.
 * 
 * @param ht 
 * @return uint8_t* 
 */
uint8_t *huffman_table_get_length_vector(struct huff_table *ht){

    return ht->htables_nb_symb_per_lengths;

}

/**
 * @brief Free the memory allocated to the huffman tree.
 * 
 * @param ht 
 */
void huffman_table_destroy(struct huff_table *ht){
    free(ht->huffcode_table);
    free(ht);
}


