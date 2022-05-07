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
void encode(bitstream *stream, struct mcu_t *mcu);

#endif /* _CONVERT_RGB_TO_YCbCr_H_.h_ */
