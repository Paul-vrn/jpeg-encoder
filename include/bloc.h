
#ifndef _BLOC_H_
#define _BLOC_H_

#include <stdint.h>


struct bloc_t {
    bloc_t *next;
    uint8_t matrice[8][8];
};

struct bloc_t *bloc_new(void);


#endif /* _BLOC_H_ */