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


uint8_t get_magnitude(int16_t number);
uint32_t get_indice_magnitude(int16_t number, uint8_t magnitude);
uint32_t codage_DC(struct bitstream1 *stream, struct vector_t *vector, uint32_t prec_DC, struct huff_table *ht);
void codage_AC(struct bitstream1 *stream, struct vector_t *vector, struct huff_table *ht);
int16_t encode_vectors(struct bitstream1 *stream, struct vector_t *vector, int16_t prec_DC, struct huff_table *htDC, struct huff_table *htAC);

#endif /* _CONVERT_RGB_TO_YCbCr_H_.h_ */
