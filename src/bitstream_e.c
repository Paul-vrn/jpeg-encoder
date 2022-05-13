#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


struct bitstream1{

    FILE *fg;
    uint32_t buff;
    int nb_bit_buff;

};

struct bitstream1 *bitstream_create1(char *filename){

    struct bitstream1 *bitstream = calloc(1, sizeof(struct bitstream1));

    bitstream->fg = fopen(filename, "ab");

    bitstream->buff = 0;

    bitstream->nb_bit_buff = 0;

    return bitstream;
}


void bitstream_destroy1(struct bitstream1 *stream){

    fclose(stream->fg);
    free(stream);



}


void bitstream_write_bits1(struct bitstream1 *stream, uint32_t value, uint8_t nb_bits, bool is_marker){

    if (stream->nb_bit_buff + nb_bits >= 8 && stream->nb_bit_buff + nb_bits < 16){

        stream->buff = (stream->buff<<(8-stream->nb_bit_buff)) + (value>>(stream->nb_bit_buff + nb_bits - 8));
        fwrite(&(stream->buff), 1, 1, stream->fg);
        stream->nb_bit_buff = stream->nb_bit_buff + nb_bits - 8;
        stream->buff = value - ((value>>(stream->nb_bit_buff + nb_bits - 8))<<(stream->nb_bit_buff + nb_bits - 8));

    } else if (stream->nb_bit_buff + nb_bits >= 16) {
    
        stream->buff = (stream->buff<<(8-stream->nb_bit_buff)) + (value>>(stream->nb_bit_buff + nb_bits - 8));
        fwrite(&(stream->buff), 1, 1, stream->fg);
        stream->buff = value - ((value>>(stream->nb_bit_buff + nb_bits - 8))<<(stream->nb_bit_buff + nb_bits - 8));
        fwrite(&(stream->buff), 1, 1, stream->fg);
        stream->nb_bit_buff = stream->nb_bit_buff + nb_bits - 16;
        stream->buff = value - ((value>>(stream->nb_bit_buff + nb_bits - 16))<<(stream->nb_bit_buff + nb_bits - 16));

    
    
    } else{

        stream->buff = (stream->buff<<nb_bits) + value;
        stream->nb_bit_buff = stream->nb_bit_buff + nb_bits;

    }

}
