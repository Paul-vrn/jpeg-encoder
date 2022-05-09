#ifndef _FREQUENTIAL_BLOC_H_
#define _FREQUENTIAL_BLOC_H_

#include <stdint.h>

struct frequential_bloc_t;

void frequential_bloc_set_next(struct frequential_bloc_t *frequential_bloc, struct frequential_bloc_t *next);

struct frequential_bloc_t* frequential_get_next(struct frequential_bloc_t *bloc);
void frequential_bloc_add(struct frequential_bloc_t **bloc, struct frequential_bloc_t *next);
int16_t frequential_bloc_get_matrice(struct frequential_bloc_t *frequential_bloc, uint8_t i, uint8_t j);

void frequential_blocs_destroy(struct frequential_bloc_t *frequential_blocs);

struct frequential_bloc_t *frequential_bloc_create(int16_t matrice[8][8]);

void frequential_bloc_print(struct frequential_bloc_t *bloc);

float coef_dct(int16_t bloc_copy[8][8], uint32_t i, uint32_t j);

struct frequential_bloc_t *dct(struct bloc_t *bloc);

#endif /* _MCU_H_ */
