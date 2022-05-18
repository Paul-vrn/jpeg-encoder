#ifndef _READ_PARAM_H_
#define _READ_PARAM_H_

#include <stdint.h>
#include <stdbool.h>

/*
    Permet la lecture des different paramètres passés en ligne de commande.
    La fonction modifie des variable passée en paramètre et donc eyant été initialisée avant
*/

void read_param(int argc, char *argv[], uint8_t *H1, uint8_t *V1, uint8_t *H2, uint8_t *V2, uint8_t *H3, uint8_t *V3, char **OUTFILE, char **INFILE);


#endif /* _READ_PARAM_H_ */