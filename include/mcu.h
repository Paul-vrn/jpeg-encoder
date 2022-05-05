#ifndef _MCU_H_
#define _MCU_H_

#include <stdint.h>
#include "bloc.h"
/**
 * @brief structure to represent a MCU
 * 
 */
struct mcu_t;

void mcu_set_next(struct mcu_t *mcu, struct mcu_t *next);
void mcu_set_Y(struct mcu_t *mcu, struct bloc_t *Y);
void mcu_set_Cb(struct mcu_t *mcu, struct bloc_t *Cb);
void mcu_set_Cr(struct mcu_t *mcu, struct bloc_t *Cr);
struct bloc_t* mcu_get_Y(struct mcu_t *mcu);
struct bloc_t* mcu_get_Cb(struct mcu_t *mcu);
struct bloc_t* mcu_get_Cr(struct mcu_t *mcu);
struct mcu_t* mcu_get_next(struct mcu_t *mcu);

struct mcu_t *mcu_create(struct bloc_t *Y, struct bloc_t *Cb, struct bloc_t *Cr);

void mcu_destroy(struct mcu_t *mcu);

void mcu_print(struct mcu_t *mcu);

void mcu_sous_echantillonne(struct mcu_t *mcu);


#endif /* _MCU_H_ */