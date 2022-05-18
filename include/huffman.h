#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include <stdint.h>
#include <stdbool.h>

struct huff_table{

    uint8_t *htables_nb_symb_per_lengths;
    uint8_t *htables_symbols;
    uint8_t nb_symbols;
    uint32_t *huffcode_table;

};
struct node;
struct node *createNode();
void node_destroy(struct node *node);
bool recursif(struct node *currentNode, uint32_t code, uint32_t depth, uint32_t *huffcode_table, uint32_t *index);
uint32_t *huffcode_table_build(struct huff_table *hufftable);
uint32_t huffman_table_get_path(struct huff_table *ht, uint8_t value, uint8_t *nb_bits);
struct huff_table *huffman_table_build(uint8_t *nb_symb_per_lengths, uint8_t *symbols, uint8_t nb_symbols);
uint8_t *huffman_table_get_symbols(struct huff_table *ht);
uint8_t *huffman_table_get_length_vector(struct huff_table *ht);
void huffman_table_destroy(struct huff_table *ht);

#endif /* _HUFFMAN_H_ */