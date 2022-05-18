/**
 * @file encoding.c
 * @author your name (you@domain.com)
 * @brief file containing every function related to encoding the image
 * @version 0.1
 * @date 2022-05-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include "htables.h"
#include "bitstream.h"
#include "vector.h"
#include "mcu.h"
#include "jpeg_writer.h"
#include "huffman.h"
#include "huffman_tree.h"

/**
 * @brief return the magnitude of the number
 * @test✔️
 * @param vector 
 */
uint8_t get_magnitude(int16_t number){
    uint8_t bits_needed = 0;
    if (number < 0){
        number = -number;
    }
    while (number > 0){
        number = number >> 1;
        bits_needed++;
    }
    return bits_needed;
}


/**
 * @brief return the indice of the magnitude of the number
 * @test✔️
 * @param number
 * @param magnitude 
 */
uint32_t get_indice_magnitude(int16_t number, uint8_t magnitude){
    uint32_t min_value = pow(2, magnitude-1);
    uint32_t max_value = pow(2, magnitude) - 1;
    if (number < 0){
        return max_value + number;
    } else {
        return (max_value - min_value) + (number - min_value) +1;
    }
}

/**
 * @brief encode the DC value in the stream
 * @test✔️ 
 * @param vector 
 * @param stream 
 * @param prec_DC 
 * @param color 
 * @return int16_t 
 */
uint32_t codage_DC(struct bitstream1 *stream, struct vector_t *vector, uint32_t prec_DC, struct huff_table *ht){
    int32_t valeur = vector_get(vector, 0) - prec_DC;
    int16_t magnitude = get_magnitude(valeur);
    uint32_t indice = get_indice_magnitude(valeur, magnitude);
    uint8_t *nb_bits = calloc(1, sizeof(uint8_t));
    uint32_t value = huffman_table_get_path(ht, magnitude, nb_bits);
    bitstream_write_bits1(stream, value, *nb_bits, false);
    bitstream_write_bits1(stream, indice, magnitude, false);
    free(nb_bits);
    return vector_get(vector, 0);
}

/**
 * @brief encode the AC values in the stream
 * @test✔️
 * @param vector 
 * @param color 
 */
void codage_AC(struct bitstream1 *stream, struct vector_t *vector, struct huff_table *ht )
{
    uint8_t coef_0 = 0;
    uint8_t nb_F0 = 0;
    uint8_t *nb_bits = calloc(1, sizeof(uint8_t));
    uint32_t value = 0;
    uint32_t value_huff = 0;
    for (uint8_t i = 1; i < 64; i++){
        if (i == 63){
            value = 0x00;
            value_huff = huffman_table_get_path(ht, value, nb_bits);
            bitstream_write_bits1(stream, value_huff, *nb_bits, false);
        } else {
            if (vector_get(vector, i) == 0)
            {
                coef_0++;
                if (coef_0 >= 16)
                {   
                    coef_0 = 0;
                    nb_F0++;
                }
            } else {
                while(nb_F0 > 0){
                    value = 0xF0;
                    value_huff = huffman_table_get_path(ht, value, nb_bits);
                    bitstream_write_bits1(stream, value_huff, *nb_bits, false);
                    nb_F0--;
                }
                value = vector_get(vector, i);
                uint8_t magnitude = get_magnitude(value);
                uint32_t index = get_indice_magnitude(value, magnitude);
                value_huff = (coef_0 << 4) + magnitude;
                value_huff = huffman_table_get_path(ht, value_huff, nb_bits);
                bitstream_write_bits1(stream, value_huff, *nb_bits, false);
                bitstream_write_bits1(stream, index, magnitude, false);
                coef_0 = 0;
            }
        }
    }
    free(nb_bits);
}

/**
 * @brief encode the vectors in the stream
 * @test✔️
 * @param stream 
 * @param vector 
 * @param color 
 */
int16_t encode_vectors(struct bitstream1 *stream, struct vector_t *vector, int16_t prec_DC, struct huff_table *htDC, struct huff_table *htAC){
    struct vector_t *current_vector = vector;
    while (current_vector != NULL){
        prec_DC = codage_DC(stream, current_vector, prec_DC, htDC);
        codage_AC(stream, current_vector, htAC);
        current_vector = vector_get_next(current_vector);
    }
    
    return prec_DC;
}
