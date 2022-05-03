
#ifndef _MCU_H_
#define _MCU_H_

#include <stdint.h>
#include "bloc.h"
/**
 * @brief structure to represent a MCU
 * 
 */
struct mcu_t {
    bloc_t *Y;
    bloc_t *Cb;
    bloc_t *Cr;
    mcu_t *next;
};



#endif /* _MCU_H_ */