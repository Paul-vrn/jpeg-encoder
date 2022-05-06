#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdint.h>
#include "bloc.h"
struct vector_t;

struct vector_t* create_vector(struct bloc_t *bloc);
void quantification(struct vector_t **vector);
void codage_dc(struct vector_t *vector);
void codage_ac(struct vector_t *vector);
void vector_dc_ac(struct vector_t *vector);
void vectors_destroy(struct vector_t *vector);
uint32_t get_bits_needed(int16_t number);


#endif /* _VECTOR_H_ */