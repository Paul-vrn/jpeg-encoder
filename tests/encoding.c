#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "htables.h"
#include "huffman.h"
#include "bitstream.h"
#include "jpeg_writer.h"
#include "vector.h"
#include <assert.h>
#include "encoding.h"

void test_get_magnitude(){
    int16_t test[11] = {0, 1, -1, 2, -3, 4, -5, 25, 63, 64, 2047};
    uint8_t res[11] = {0, 1, 1, 2, 2, 3, 3, 5, 6, 7, 11};
    for (uint32_t i = 0; i < 11; i++)
    {
        assert(get_magnitude(test[i]) == res[i]);
    }
}

void test_indice(){
    int16_t value[5] =     {94, -199, 174, 2, -18};
    uint8_t magnitude[5] = {7, 8, 8, 2, 5};
    uint32_t res[5] =      {94, 56, 174, 2, 13};
    uint32_t val = 0;
    for (uint32_t i = 0; i < 5; i++)
    {
        val = get_indice_magnitude(value[i], magnitude[i]);
        printf("%d == %d \n", val, res[i]);
        assert(val == res[i]);
    }
}

void test_huffman_DC()
{
    int16_t tab [64] = { 
        0xff49 ,0xffe1 ,0x0001 ,0xffe8 ,0xffff ,0x0002 ,0x0000 ,0x0000,
        0x001e ,0xfffb ,0x0016 ,0x0003 ,0xfffc ,0x0000 ,0x0000 ,0x0000,
        0x0000 ,0x0000 ,0xfffe ,0xfff3 ,0x0002 ,0xfffe ,0xffff ,0x0001,
        0x0000 ,0xfffe ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000,
        0x0000 ,0x0002 ,0x0004 ,0xfffe ,0x0002 ,0x0000 ,0x0000 ,0x0000,
        0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000,
        0xffff ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000,
        0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000
     };
    struct vector_t *vect = create_vector(tab);
    struct bitstream *bt = bitstream_create("test.jpeg");
    int16_t *prec = calloc(1, sizeof(int16_t));
    *prec = 0xffc6;
    *prec = encode_vectors(bt, vect, Y, *prec);
    printf("%d\n", *prec);
}


void test_encoding(){
    struct huff_table *ht = huffman_table_build(
        htables_nb_symb_per_lengths[DC][Y],
        htables_symbols[DC][Y],
        htables_nb_symbols[DC][Y]
    );
//    uint8_t *nb_bits = calloc(1, sizeof(uint8_t));
    uint8_t *nb_bits = calloc(1, sizeof(uint8_t));
    uint8_t val = 0xffe0 - 0xff82;
    printf("%d\n", val);
    uint8_t magnitude = get_magnitude(val);
    uint32_t indice = get_indice_magnitude(val, magnitude);
    printf("magnitude = %d\n", magnitude);
    printf("indice = %d\n", indice);
    uint32_t value = huffman_table_get_path(ht, magnitude, nb_bits);
    //-32+126 = 94
    printf("chemin = %d\n", value);
    printf("nb bits = %d\n", *nb_bits);
}

int main(void)
{
    printf("test encoding!\n");
    test_huffman_DC();
    return EXIT_SUCCESS;
}


