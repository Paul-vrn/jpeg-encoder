#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "huffman_tree.h"
#include "bitstream_e.h"



enum color_component{
    Y,
    Cb,
    Cr,
    NB_COLOR_COMPONENTS
};

enum sample_type{
    DC,
    AC,
    NB_SAMPLE_TYPES
};

enum direction{
    H,
    V,
    NB_DIRECTIONS
};


struct jpeg1{

    const char *filename;
    const char *out_filename;
    uint32_t height;
    uint32_t width;
    uint8_t nb_component;
    uint8_t sample[3][2];
    struct huff_table1 *huff[3][2];
    uint8_t *qtable[3];

};

struct jpeg1 *jpeg_create1(void){

    struct jpeg1 *jpeg1 = calloc(1, sizeof(struct jpeg1));
    return jpeg1;

}

void jpeg_destroy1(struct jpeg1 *jpg){

    free(jpg);

}

void jpeg_set_ppm_filename1(struct jpeg1 *jpg, const char *ppm_filename){

    jpg->filename = ppm_filename;

}

void jpeg_set_jpeg_filename1(struct jpeg1 *jpg, const char *jpeg1_filename){

    jpg->out_filename = jpeg1_filename;

}

void jpeg_set_image_height1(struct jpeg1 *jpg, uint32_t image_height){

    jpg->height = image_height;

}

void jpeg_set_image_width1(struct jpeg1 *jpg, uint32_t image_width){

    jpg->width = image_width;

}

void jpeg_set_nb_components1(struct jpeg1 *jpg, uint8_t nb_components){

    jpg->nb_component = nb_components;

}

void jpeg_set_sampling_factor1(struct jpeg1 *jpg, enum color_component cc, enum direction dir, uint8_t sampling_factor){

    jpg->sample[cc][dir] = sampling_factor;

}


void jpeg_set_huffman_table1(struct jpeg1 *jpg, enum sample_type acdc, enum color_component cc, struct huff_table1 *htable){

    jpg->huff[cc][acdc] = htable;

}

void jpeg_set_quantization_table1(struct jpeg1 *jpg, enum color_component cc, uint8_t *qtable){

    jpg->qtable[cc] = qtable;

}

void jpeg_write_header1(struct jpeg1 *jpg){


    FILE *fg = fopen(jpg->out_filename, "wb");
    
    /* Marqueur de début d'image */
    uint16_t val = 0xd8ff;
    uint16_t *pt = &val;
    fwrite(pt, 1, 2, fg);
    /* Application Data */
    *pt = 0xe0ff;
    fwrite(pt, 1, 2, fg);
    *pt = 0x1000;
    fwrite(pt, 1, 2, fg);
    *pt = 0x464a;
    fwrite(pt, 1, 2, fg);
    *pt = 0x4649;
    fwrite(pt, 1, 2, fg);
    *pt = 0x0100;
    fwrite(pt, 1, 2, fg);
    *pt = 0x0001;
    fwrite(pt, 1, 2, fg);
    *pt = 0x000;
    fwrite(pt, 1, 2, fg);
    fwrite(pt, 1, 2, fg);
    fwrite(pt, 1, 2, fg);

    /* Commentaire */
    *pt = 0xfeff;
    fwrite(pt, 1, 2, fg);
    *pt = 0x1000; // On part du principe qu'il n'y en a pas
    fwrite(pt, 1, 2, fg);
    *pt = 0x333c;
    fwrite(pt, 1, 2, fg);
    *pt = 0x6c20;
    fwrite(pt, 1, 2, fg);
    *pt = 0x2065;
    fwrite(pt, 1, 2, fg);
    *pt = 0x7270;
    fwrite(pt, 1, 2, fg);
    *pt = 0x6a6f;
    fwrite(pt, 1, 2, fg);
    *pt = 0x7465;
    fwrite(pt, 1, 2, fg);
    *pt = 0x4320;
    fwrite(pt, 1, 2, fg);



    /* Define Quantization Table */
    uint16_t loop = (jpg->nb_component == 1) ? 1 : 2;
    for (uint16_t i = 0; i < loop; i++){
        *pt = 0xdbff;
        fwrite(pt, 1, 2, fg);
        *pt = 0x4300;
        fwrite(pt, 1, 2, fg);
        *pt = i;
        fwrite(pt, 1, 1, fg);
        for (int j = 0; j < 64; j++){

            *pt = (uint16_t)jpg->qtable[i][j];
            fwrite(pt, 1, 1, fg);

        }
    }

    /* Start Of Frame */
    *pt = 0xc0ff;
    fwrite(pt, 1, 2, fg);
    *pt = ((3*jpg->nb_component + 8)<<8) + ((3*jpg->nb_component + 8)>>8);
    fwrite(pt, 1, 2, fg);
    *pt = 0x08;
    fwrite(pt, 1, 1, fg);
    *pt = ((uint16_t)jpg->height<<8) + ((uint16_t)jpg->height>>8);
    fwrite(pt, 1, 2, fg);
    *pt = ((uint16_t)jpg->width<<8) + ((uint16_t)jpg->width>>8);
    fwrite(pt, 1, 2, fg);
    *pt = (uint16_t)jpg->nb_component;
    fwrite(pt, 1, 1, fg);
    for (uint16_t i = 1; i < jpg->nb_component + 1; i++){
        *pt = i;
        fwrite(pt, 1, 1, fg);
        *pt = jpg->sample[i-1][0] + jpg->sample[i-1][1]*16;
        fwrite(pt, 1, 1, fg);
        *pt = i - 1;
        fwrite(pt, 1, 1, fg);
    }

    /* Define Huffman Table */
    for (uint16_t i = 0; i < loop; i++){
        for(uint16_t j = 0; j < NB_SAMPLE_TYPES; j++){

            *pt = 0xc4ff;
            fwrite(pt, 1, 2, fg);

            *pt = ((2 + 17 + (uint16_t)jpg->huff[i][j]->nb_symbols)<<8) + ((2 + 17 + (uint16_t)jpg->huff[i][j]->nb_symbols)>>8); //PB
            fwrite(pt, 1, 2, fg);

            *pt = j*16 + i;
            fwrite(pt, 1, 1, fg);

            for (uint8_t h = 0; h < 16; h++){

                *pt = jpg->huff[i][j]->htables_nb_symb_per_lengths[h];
                fwrite(pt, 1, 1, fg);

            }

            for (uint8_t h = 0; h < jpg->huff[i][j]->nb_symbols; h++){

                *pt = jpg->huff[i][j]->htables_symbols[h];
                fwrite(pt, 1, 1, fg);

            }

        }

    }

    /* Start Of Scan */
    *pt = 0xdaff;
    fwrite(pt, 1, 2, fg);
    *pt = ((6 + 2*(uint16_t)jpg->nb_component)<<8) + ((6 + 2*(uint16_t)jpg->nb_component)>>8);
    fwrite(pt, 1, 2, fg); //PB
    *pt = (uint16_t)jpg->nb_component;
    fwrite(pt, 1, 1, fg);
    for (uint16_t i = 1; i < jpg->nb_component + 1; i++){
        *pt  = i;
        fwrite(pt, 1, 1, fg);
        *pt = (i-1) + (i-1)*16;
        fwrite(pt, 1, 1, fg);
        
    }

    *pt = 0;
    fwrite(pt, 1, 1, fg);
    *pt = 63;
    fwrite(pt, 1, 1, fg);
    *pt = 0;
    fwrite(pt, 1, 1, fg);

    fclose(fg);

}


void jpeg_write_footer1(struct jpeg1 *jpg){

    FILE *fg = fopen(jpg->out_filename, "ab");

    uint16_t val = 0xd9ff;
    uint16_t *pt = &val;
    fwrite(pt, 1, 2, fg);
    fclose(fg);

}

struct bitstream1 *jpeg_get_bitstream1(struct jpeg1 *jpg){

    struct bitstream1 *bitstream = bitstream_create1(jpg->out_filename);
    return bitstream;

}

