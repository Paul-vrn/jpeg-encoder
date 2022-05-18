#ifndef _BLOC_H_
#define _BLOC_H_

#include <stdint.h>
#include <stdbool.h>

struct bloc_t;

void bloc_set_next(struct bloc_t *bloc, struct bloc_t *next);
void bloc_set_matrice(struct bloc_t *bloc, uint8_t matrice[8][8]);
struct bloc_t *bloc_get_next(struct bloc_t *bloc);
uint8_t bloc_get_matrice(struct bloc_t *bloc, uint32_t i, uint32_t j);
void bloc_add(struct bloc_t **bloc, struct bloc_t *next);
struct bloc_t *bloc_create(uint8_t matrice[8][8]);
struct bloc_t* bloc_create_from_pixels(uint8_t **pixels, uint32_t start_x, uint32_t end_x, uint32_t start_y, uint32_t end_y);
void blocs_destroy(struct bloc_t **head);
void bloc_print(struct bloc_t *bloc);
void blocs_print(struct bloc_t *blocs);
void blocs_fusion(struct bloc_t **blocs, uint32_t H1, uint32_t V1, uint32_t H2, uint32_t V2);


#endif /* _BLOC_H_ */
