#ifndef _MCU_H_
#define _MCU_H_

#include <stdint.h>

struct frequential_bloc_t;


void frequential_blocs_destroy(struct frequential_bloc_t *frequential_blocs);

struct frequential_bloc_t *frequential_bloc_create(int16_t matrice[8][8]);

void frequential_bloc_print(struct frequential_bloc_t *bloc);

float coef_dct(int16_t bloc_copy[8][8], uint32_t i, uint32_t j);

struct frequential_bloc_t *dct(uint8_t bloc[8][8]);

#endif /* _MCU_H_ */