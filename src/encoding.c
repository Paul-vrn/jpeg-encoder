#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "htables.h"
#include "bitstream.h"
#include "vector.h"
#include "mcu.h"
#include "jpeg_writer.h"

/**
 * @brief
 * @test✔️
 * @param vector 
 */
uint32_t get_magnitude(int16_t number){
    uint32_t bits_needed = 0;
    if (number < 0){
        number = -number;
    }
    while (number > 0){
        number = number >> 1;
        bits_needed++;
    }
    return bits_needed;
}
uint32_t get_indice_magnitude(int16_t number, uint32_t magnitude){
    return number + -2**magnitude-1;
}


/**
 * @brief 
 * 
 * @param stream 
 * @param mcu 
 */
void encode(bitstream *stream, struct mcu_t *mcu)
{
    struct mcu_t *current_mcu = mcu;
    while (current != NULL){
        encode_vectors(stream, mcu_get_vectorY(current_mcu), 0);
        encode_vectors(stream, mcu_get_vectorCb(current_mcu), 1);
        encode_vectors(stream, mcu_get_vectorCr(current_mcu), 2);
        current = current->next;
    }
}


/**
 * @brief 
 * 
 * @param stream 
 * @param vector 
 * @param color 
 */
void encode_vectors(bitstream *stream, struct vector_t *vector, uint8_t color){
    struct vector_t *current_vector = vector;
    int16_t *prec_DC = NULL;
    while (current_vector != NULL){
        *prec_DC = codage_DC(stream, current_vector, prec_DC, color);
        codage_AC(stream, current_vector, color);
        current_vector = current_vector->next;
    }
    
}


/**
 * @brief 
 * 
 * @param vector 
 * @param stream 
 * @param prec_DC 
 * @param color 
 * @return int16_t 
 */
int16_t codage_DC(struct vector_t *vector, bitstream *stream, uint16_t prec_DC, uint8_t color){
    if (prec_DC == NULL){
        // pas en fonction de prec_DC
    } else {
        // en fonction de prec_DC
    }
}


/*
extern void bitstream_write_bits(struct bitstream *stream,
                                 uint32_t value,
                                 uint8_t nb_bits,
                                 bool is_marker);
*/

/**
 * @brief Construct a new codage RLE AC object
 * 
 * @param vector 
 * @param color 
 */
codage_RLE_AC(struct vector_t *vector, uint8_t color)
{
    uint8_t coef_0 = 0;
    uint8_t nb_F0 = 0;
    for (uint8_t i = 1; i < 64; i++){
        if (i == 63){
            bitstream_write_bits(0x00, 1, false);
        } else {
        if (vector_get(vector, i) == 0){ // si bloque == 0
            coef_0++;
            if (coef_0 == 16)
            {
                coef_0 = 0;
                nb_F0++;
            }
        } else {
            for (nb_F0; nb_F0 > 0; nb_F0--){
                bitstream_write_bits(0xF0, 1, false); // taille pas bonne
            }
            value = vector_get(vector, i);
            uint8_t magnitude = get_magnitude(value);
            uint8_t index = get_indice_magnitude(value, magnitude){
            value_huff = (coef_0 << 4) + magnitude;
            //passe value_huff dans huffman
            bitstream_write_bits(index, magnitude, false);
        }

}