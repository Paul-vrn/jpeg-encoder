#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



struct huff_table1{

    uint8_t *htables_nb_symb_per_lengths;
    uint8_t *htables_symbols;
    uint8_t nb_symbols;

};

struct huff_table1 *huffman_table_build1(uint8_t *nb_symb_per_lengths, uint8_t *symbols, uint8_t nb_symbols){

    struct huff_table1 *table = calloc(1, sizeof(struct huff_table1));

    table->htables_nb_symb_per_lengths = nb_symb_per_lengths;
    table->htables_symbols = symbols;
    table->nb_symbols = nb_symbols;

    return table;

}


uint8_t *huffman_table_get_symbols1(struct huff_table1 *ht){

    return ht->htables_symbols;

}

uint8_t *huffman_table_get_length_vector1(struct huff_table1 *ht){

    return ht->htables_nb_symb_per_lengths;

}

void huffman_table_destroy1(struct huff_table1 *ht){

    free(ht);
}

uint32_t huffman_table_get_path1(struct huff_table1 *ht, uint8_t value, uint8_t *nb_bits){

    



}
