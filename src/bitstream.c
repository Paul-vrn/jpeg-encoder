/**
 * @file bitstream.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief A struct that represents a bitstream used to write bits into the jpeg file
 * 
 */
struct bitstream{

    FILE *fg;
    uint32_t buff;
    int nb_bit_buff;

};

/**
 * @brief Initialize a new bitstream, allowing us to write bits into the given input file
 * 
 * @param[in] filename 
 * @return struct bitstream* 
 */
struct bitstream *bitstream_create(char *filename){

    struct bitstream *bitstream = calloc(1, sizeof(struct bitstream));

    bitstream->fg = fopen(filename, "ab");

    bitstream->buff = 0;

    bitstream->nb_bit_buff = 0;

    return bitstream;
}

/**
 * @brief Free the memory allocated to the bitstream and close the file
 * 
 * @param[in] stream 
 */
void bitstream_destroy(struct bitstream *stream){

    fclose(stream->fg);
    free(stream);



}

/**
 * @brief Write bits into the bitstream when they are 8 bits in the buffer
 * 
 * @param[in] stream 
 * @param[in] value 
 * @param[in] nb_bits 
 */
void bitstream_write_bits(struct bitstream *stream, uint32_t value, uint8_t nb_bits){

    uint8_t trash = 0;
    value = value - ((value>>nb_bits)<<nb_bits); 

    if (stream->nb_bit_buff + nb_bits >= 8 && stream->nb_bit_buff + nb_bits < 16){

        stream->buff = (stream->buff<<(8-stream->nb_bit_buff)) + (value>>(stream->nb_bit_buff + nb_bits - 8));
        fwrite(&(stream->buff), 1, 1, stream->fg);
        if ((uint8_t)stream->buff == 0xff){


            fwrite(&trash, 1, 1, stream->fg);

        }
        stream->buff = value - ((value>>(stream->nb_bit_buff + nb_bits - 8))<<(stream->nb_bit_buff + nb_bits - 8));
        stream->nb_bit_buff = stream->nb_bit_buff + nb_bits - 8;
        

    } else if (stream->nb_bit_buff + nb_bits >= 16) {
    
        stream->buff = (stream->buff<<(8-stream->nb_bit_buff)) + (value>>(stream->nb_bit_buff + nb_bits - 8));
        fwrite(&(stream->buff), 1, 1, stream->fg);
        if ((uint8_t)stream->buff == 0xff){

            fwrite(&trash, 1, 1, stream->fg);

        }
        stream->buff = (value - ((value>>(stream->nb_bit_buff + nb_bits - 8))<<(stream->nb_bit_buff + nb_bits - 8)))>>(stream->nb_bit_buff + nb_bits - 16);
        fwrite(&(stream->buff), 1, 1, stream->fg);
        if ((uint8_t)stream->buff == 0xff){

            fwrite(&trash, 1, 1, stream->fg);

        }
        stream->buff = value - ((value>>(stream->nb_bit_buff + nb_bits - 16))<<(stream->nb_bit_buff + nb_bits - 16));
        stream->nb_bit_buff = stream->nb_bit_buff + nb_bits - 16;
        

    
    
    } else{

        stream->buff = (stream->buff<<nb_bits) + value;
        stream->nb_bit_buff = stream->nb_bit_buff + nb_bits;

    }

    // printf("nb_bit = %i\n", stream->nb_bit_buff);
    // printf("buff = %u\n", stream->buff);

}


/**
 * @brief Use a the end of the bitstream to write the last bits contained in the buffer.
 * 
 * @param[in] stream 
 */
void bitstream_flush(struct bitstream *stream){

    if (stream->nb_bit_buff != 0){

        stream->buff = (stream->buff<<(8 - stream->nb_bit_buff));
        fwrite(&(stream->buff), 1, 1, stream->fg);

    }

}
