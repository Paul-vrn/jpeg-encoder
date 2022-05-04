
#ifndef _BLOC_H_
#define _BLOC_H_

#include <stdint.h>

struct bloc_t;

struct bloc_t *bloc_create(uint8_t matrice[8][8]);
struct bloc_t* bloc_create_from_pixels(uint8_t **matrice, uint32_t start_x, uint32_t end_x, uint32_t start_y, uint32_t end_y);

void bloc_destroy(struct bloc_t *bloc);
void blocs_destroy(struct bloc_t *blocs);

void bloc_print(struct bloc_t *bloc);

void blocs_fusion(struct bloc_t **blocs);

struct bloc_t* fusion_2_blocs(struct bloc_t *bloc1, struct bloc_t *bloc2);

struct bloc_t* fusion_4_blocs(struct bloc_t *bloc1, struct bloc_t *bloc2, struct bloc_t *bloc3, struct bloc_t *bloc4);

#endif /* _BLOC_H_ */