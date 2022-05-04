
#ifndef _MCU_H_
#define _MCU_H_

#include <stdint.h>
#include "bloc.h"
/**
 * @brief structure to represent a MCU
 * 
 */
struct mcu_t;

struct mcu_t *mcu_create(struct bloc_t *Y, struct bloc_t *Cb, struct bloc_t *Cr);

void mcu_destroy(struct mcu_t *mcu);

void mcu_print(struct mcu_t *mcu);

void mcu_sous_echantillonne(struct mcu_t *mcu);


#endif /* _MCU_H_ */