#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "htables.h"
#include "huffman.h"
#include "bitstream.h"
#include "jpeg_writer.g"

void test_get_bits_needed(){
    int16_t test[11] = {0, 1, -1, 2, -3, 4, -5, 25, 63, 64, 2047};
    uint32_t res[11] = {0, 1, 1, 2, 2, 3, 3, 5, 6, 7, 11};
    for (uint32_t i = 0; i < 11; i++)
    {
        assert(get_bits_needed(test[i]) == res[i]);
    }
}


void test_huffman_DC()
{
    uint16_t tab [64] = { 
        0xff49 ,0xffe1 ,0x0001 ,0xffe8 ,0xffff ,0x0002 ,0x0000 ,0x0000,
        0x001e ,0xfffb ,0x0016 ,0x0003 ,0xfffc ,0x0000 ,0x0000 ,0x0000,
        0x0000 ,0x0000 ,0xfffe ,0xfff3 ,0x0002 ,0xfffe ,0xffff ,0x0001,
        0x0000 ,0xfffe ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000,
        0x0000 ,0x0002 ,0x0004 ,0xfffe ,0x0002 ,0x0000 ,0x0000 ,0x0000,
        0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000,
        0xffff ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000,
        0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000 ,0x0000
     }
    struct vector_t *vect = create_vector(tab);
    struct bitstream *bt = bitstream_create("test.jpeg");
    encode_vectors(bt, vect, Y);
}


int main(void)
{
    printf("test encoding!\n");
    test_huffman_DC();
    return EXIT_SUCCESS;
}


