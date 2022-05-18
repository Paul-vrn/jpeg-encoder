#ifndef _READ_PIC_H_
#define _READ_PIC_H_

#include <stdint.h>
#include <stdbool.h>


/*
    Creer trois tableau de nombre (RGB) a partir de l'imgae ppm passée en paramètre
    Si l'image est en niveau de gris, les tableau G et B sont NULL
*/
uint8_t ***creat_matrix(uint32_t *height, uint32_t *width, uint8_t *type, char **filename);


/*
    Libère la mémoir occupé par la matrice contenant l'image ppm
*/
void free_matrix(uint8_t ***matrix);

#endif /* _READ_PIC_H_ */