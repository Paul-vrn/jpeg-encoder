#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "htables.h"
#include "huffman.h"
#include "bitstream.h"
#include "jpeg_writer.g"

void test_huffman_DC()
{
    struct huff_table *ht = huffman_table_build(
        htables_nb_symb_per_lengths[sample_type.DC][color_component.Y][16],
        htables_symbols[sample_type.DC][Y],
        htables_nb_symbols[sample_type.DC][color_component.Y]
    )
    uint8_t *nb_bits = calloc(1, sizeof(uint8_t));
    uint32_t value = huffman_table_get_path(ht, 77, nb_bits);
    printf("%d\n", value);
    printf("%d\n", *nb_bits);
}


int main(void)
{
    printf("test encoding!\n");
    test_huffman_DC();
    return EXIT_SUCCESS;
}


