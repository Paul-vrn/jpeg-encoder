#ifndef _MCU_H_
#define _MCU_H_

#include <stdint.h>
#include "bloc.h"
#include "frequential_bloc.h"
#include "bitstream.h"
#include "huffman.h"

struct mcu_t;

struct mcu_t;
struct mcu_t *mcu_get_by_id(struct mcu_t *head, uint32_t i);
struct mcu_t *mcu_create(struct bloc_t *Y, struct bloc_t *Cb, struct bloc_t *Cr);
void mcus_destroy(struct mcu_t **head);
void mcu_print(struct mcu_t *mcu);
void mcus_print(struct mcu_t *mcu);
void mcu_add(struct mcu_t **mcu, struct mcu_t *next);
void mcu_downsampling(struct mcu_t *mcu, uint32_t H1, uint32_t V1, uint32_t H2, uint32_t V2, uint32_t H3, uint32_t V3);
void mcus_downsampling(struct mcu_t *mcu, uint32_t H1, uint32_t V1, uint32_t H2, uint32_t V2, uint32_t H3, uint32_t V3);
struct mcu_t* decoupage_mcu(uint8_t **pixels[3], uint32_t height, uint32_t width, uint32_t H1, uint32_t V1);
void mcu_quantification(struct mcu_t *mcu);
void mcu_encode(struct bitstream *stream, struct mcu_t *mcu, struct huff_table *ht_DC_Y,    struct huff_table *ht_AC_Y, struct huff_table *ht_DC_CbCr, struct huff_table *ht_AC_CbCr);
void mcu_zigzag(struct mcu_t* mcu);
void mcu_dct(struct mcu_t* mcu);

#endif /* _MCU_H_ */