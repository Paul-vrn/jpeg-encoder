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

/**
 * @brief
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
 * @brief
 * @test✔️ (~)
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
 * @brief 
 * @test✔️ 
 * @param vector 
 * @param stream 
 * @param prec_DC 
 * @param color 
 * @return int16_t 
 */
int16_t codage_DC(struct bitstream1 *stream, struct vector_t *vector, int16_t prec_DC, struct huff_table *ht){
    int16_t valeur = vector_get(vector, 0) - prec_DC;
    int16_t magnitude = get_magnitude(valeur);
    int16_t indice = get_indice_magnitude(valeur, magnitude);
    uint8_t *nb_bits = calloc(1, sizeof(uint8_t));
    uint32_t value = huffman_table_get_path(ht, magnitude, nb_bits);
    bitstream_write_bits1(stream, value, *nb_bits, false);
    //printf("bitstream => writing %d over %d bits\n", value, *nb_bits);
    bitstream_write_bits1(stream, indice, magnitude, false);
    //printf("bitstream => writing %d over %d bits\n", indice, magnitude);
    return vector_get(vector, 0);
}

/**
 * @brief Construct a new codage RLE AC object
 * @test✔️ (à 90% sur) 
 * @param vector 
 * @param color 
 */
void codage_AC(struct bitstream1 *stream, struct vector_t *vector, struct huff_table *ht )
{
    uint8_t coef_0 = 0;
    uint8_t nb_F0 = 0;
    uint8_t *nb_bits = calloc(1, sizeof(uint8_t));
    int16_t value = 0;
    uint32_t value_huff = 0;
    for (uint8_t i = 1; i < 64; i++){
        if (i == 63){
            //printf("value = endofblock\n");
            value = 0x00;
            value_huff = huffman_table_get_path(ht, value, nb_bits);
            bitstream_write_bits1(stream, value_huff, *nb_bits, false);
            //printf("bitstream => writing %d over %d bits\n", value, *nb_bits);
        } else {
            if (vector_get(vector, i) == 0)
            { // si bloque == 0
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
                    //printf("bitstream => writing %d over %d bits\n", value_huff, *nb_bits);
                    nb_F0--;
                }
                value = vector_get(vector, i);
                uint8_t magnitude = get_magnitude(value);
                uint8_t index = get_indice_magnitude(value, magnitude);
                value_huff = (coef_0 << 4) + magnitude;
                value_huff = huffman_table_get_path(ht, value_huff, nb_bits);
                bitstream_write_bits1(stream, value_huff, *nb_bits, false);
                //printf("bitstream => writing %d over %d bits\n", value_huff, *nb_bits);
                bitstream_write_bits1(stream, index, magnitude, false);
                //printf("bitstream => writing %d over %d bits\n", index, magnitude);
                coef_0 = 0;
            }
        }
    }
}

/**
 * @brief 
 * @test✔️
 * @param stream 
 * @param vector 
 * @param color 
 */
int16_t encode_vectors(struct bitstream1 *stream, struct vector_t *vector, enum color_component color, int16_t prec_DC){
    struct vector_t *current_vector = vector;
    struct huff_table *htDC = huffman_table_build(
        htables_nb_symb_per_lengths[DC][(color == Y) ? Y:Cb],
        htables_symbols[DC][(color == Y) ? Y:Cb],
        htables_nb_symbols[DC][(color == Y) ? Y:Cb]
    );
    struct huff_table *htAC = huffman_table_build(
        htables_nb_symb_per_lengths[AC][(color == Y) ? Y:Cb],
        htables_symbols[AC][(color == Y) ? Y:Cb],
        htables_nb_symbols[AC][(color == Y) ? Y:Cb]
    );
    while (current_vector != NULL){
        //printf("Codage DC :\n");
        prec_DC = codage_DC(stream, current_vector, prec_DC, htDC);
        //printf("Codage AC :\n");
        codage_AC(stream, current_vector, htAC);
        current_vector = vector_get_next(current_vector);
    }
    return prec_DC;
}
