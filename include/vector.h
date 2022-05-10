#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdint.h>
#include "frequential_bloc.h"
struct vector_t;

int16_t vector_get(struct vector_t *vector, uint32_t index);
struct vector_t *vector_get_next(struct vector_t *vector);
void vector_add(struct vector_t **vector, struct vector_t *next);
struct vector_t* create_vector(int16_t tab[64]);

struct vector_t* create_vector_from_bloc(struct frequential_bloc_t *freq_bloc);
void vector_quantificationY(struct vector_t *vector);
void vector_quantificationCbCr(struct vector_t *vector);
void vectors_quantificationY(struct vector_t *vectors);

void vectors_quantificationY(struct vector_t *vectors);
void vectors_quantificationCbCr(struct vector_t *vectors);

void vectors_destroy(struct vector_t *vector);
uint32_t get_bits_needed(int16_t number);


#endif /* _VECTOR_H_ */
