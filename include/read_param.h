#ifndef _READ_PARAM_H_
#define _READ_PARAM_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Read the parameters from the command line and store them in the function parameters.
 *  These parameters need to be initialized before calling the function.
 * 
 * @param argc 
 * @param argv 
 * @param H1 
 * @param V1 
 * @param H2 
 * @param V2 
 * @param H3 
 * @param V3 
 * @param OUTFILE 
 * @param INFILE 
 */
void read_param(int argc, char *argv[], uint8_t *H1, uint8_t *V1, uint8_t *H2, uint8_t *V2, uint8_t *H3, uint8_t *V3, char **OUTFILE, char **INFILE);


#endif /* _READ_PARAM_H_ */