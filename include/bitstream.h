#ifndef _BITSTREAM_H_
#define _BITSTREAM_H_

#include <stdint.h>
#include <stdbool.h>

/*
    Structure bitstream qui permet l'ecriture dans le flux de bits du fichier jpeg
*/
struct bitstream{

    FILE *fg;
    uint32_t buff;
    int nb_bit_buff;

};

/* Initialise un nouveau bitstream */

extern struct bitstream *bitstream_create(const char *filename);

/*
    Permet d'ecrire nb_bits bit dans le bitstream. Ces bits sont contenue dans value
*/
extern void bitstream_write_bits(struct bitstream *stream,
                                 uint32_t value,
                                 uint8_t nb_bits);

/*
    Ecrit les bits réstant dans le buff a la fin de l'ecriture dans le bitstream
*/
extern void bitstream_flush(struct bitstream *stream);

/*
    Libère la mémoir du bitstream
*/
extern void bitstream_destroy(struct bitstream *stream);

#endif /* _BITSTREAM_H_ */
