#ifndef _CONVERT_RGB_TO_YCbCr_H_
#define _CONVERT_RGB_TO_YCbCr_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "htables.h"
#include "bitstream.h"
#include "vector.h"
#include "mcu.h"
#include "jpeg_writer.h"


uint32_t get_magnitude(int16_t number);
uint32_t get_indice_magnitude(int16_t number, uint32_t magnitude);
void encode(struct bitstream *stream, struct mcu_t *mcu);
void encode_vectors(struct bitstream *stream, struct vector_t *vector, enum color_component color);
int16_t codage_DC(struct vector_t *vector, struct bitstream *stream, int16_t prec_DC, struct huff_table *ht);
void codage_RLE_AC(struct vector_t *vector, struct huff_table *ht);

#endif /* _CONVERT_RGB_TO_YCbCr_H_.h_ */
