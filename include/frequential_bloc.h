#ifndef _FREQUENTIAL_BLOC_H_
#define _FREQUENTIAL_BLOC_H_

#include <stdint.h>

struct frequential_bloc_t;

int16_t frequential_bloc_get_matrice(struct frequential_bloc_t *frequential_bloc, uint8_t i, uint8_t j);
void frequential_blocs_destroy(struct frequential_bloc_t *frequential_blocs);

#endif /* _FREQUENTIAL_BLOC_H_ */
