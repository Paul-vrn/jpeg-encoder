#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_

#include <stdint.h>
#include <stdbool.h>

struct huff_table1{

    uint8_t *htables_nb_symb_per_lengths;
    uint8_t *htables_symbols;
    uint8_t nb_symbols;

};

struct huff_table1 *huffman_table_build1(uint8_t *nb_symb_per_lengths, uint8_t *symbols, uint8_t nb_symbols);

uint8_t *huffman_table_get_symbols1(struct huff_table1 *ht);

uint8_t *huffman_table_get_length_vector1(struct huff_table1 *ht);

void huffman_table_destroy1(struct huff_table1 *ht);

uint32_t huffman_table_get_path1(struct huff_table1 *ht, uint8_t value, uint8_t *nb_bits);




#endif /* _HUFFMAN_TREE_ */