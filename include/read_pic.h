#ifndef _READ_PIC_H_
#define _READ_PIC_H_

#include <stdint.h>
#include <stdbool.h>

uint8_t ***creat_matrix(uint32_t *height, uint32_t *width, uint8_t *type, char **filename);
void free_matrix(uint8_t ***matrix);

#endif /* _READ_PIC_H_ */