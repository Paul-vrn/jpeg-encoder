#ifndef _READ_PIC_H_
#define _READ_PIC_H_

#include <stdint.h>
#include <stdbool.h>


/**
 * @brief Creat 3 matrixes from the input ppm pictures. If the picture is a ppm file the 3 matrixes are for R, G and B.
 * If the picture is a pgm file the first matrixe is for gray level and the others two are NULL.
 * 
 * @param height 
 * @param width 
 * @param type 
 * @param filename 
 * @return uint8_t*** 
 */
uint8_t ***creat_matrix(uint32_t *height, uint32_t *width, uint8_t *type, char **filename);


/**
 * @brief Free the memory allocated for the matrixes.
 * 
 * @param matrix 
 */
void free_matrix(uint8_t ***matrix);

#endif /* _READ_PIC_H_ */