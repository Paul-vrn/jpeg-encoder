/**
 * @file jpeg_writer.c
 * @author Axel Perrin (axel.perrin@grenoble-inp.org)
 * @brief File to write the header of the jpeg image
 * @version 1.0
 * @date 2022-05-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "huffman.h"
#include "bitstream.h"

/**
 * @brief An Enumerated type describing the differents color types
 * 
 */
enum color_component{
    Y,
    Cb,
    Cr,
    NB_COLOR_COMPONENTS
};

/**
 * @brief An enumerated type descriping the differents sample types
 * 
 */
enum sample_type{
    DC,
    AC,
    NB_SAMPLE_TYPES
};

/**
 * @brief An enumerated type describing the differents types of sampling factors
 * 
 */
enum direction{
    H,
    V,
    NB_DIRECTIONS
};


/**
 * @brief A struct describing the JPEG image with all its header informations
 * 
 */
struct jpeg{

    const char *filename;
    const char *out_filename;
    uint32_t height;
    uint32_t width;
    uint8_t nb_component;
    uint8_t sample[3][2];
    struct huff_table *huff[3][2];
    uint8_t *qtable[3];

};

/**
 * @brief Allocate and return a new jpeg structure
 * 
 * @return struct jpeg* 
 */
struct jpeg *jpeg_create(void){

    struct jpeg *jpeg = calloc(1, sizeof(struct jpeg));
    return jpeg;

}

/**
 * @brief Destroy and free a jpeg structure
 * 
 * @param[in] jpg 
 */
void jpeg_destroy(struct jpeg *jpg){

    free(jpg);

}

/**
 * @brief Add the filname of the inpute ppm file to the jpeg structure
 * 
 * @param[in] jpg 
 */ 
void jpeg_set_ppm_filename(struct jpeg *jpg, const char *ppm_filename){

    jpg->filename = ppm_filename;

}

/**
 * @brief Add the filename of the outpute jpeg file to the jpeg structure
 * 
 * @param[in] jpg 
 * @param[in] jpeg_filename 
 */
void jpeg_set_jpeg_filename(struct jpeg *jpg, const char *jpeg_filename){

    jpg->out_filename = jpeg_filename;

}

/**
 * @brief Set the height of the image to the jpeg structure
 * 
 * @param[in] jpg 
 * @param[in] image_height 
 */
void jpeg_set_image_height(struct jpeg *jpg, uint32_t image_height){

    jpg->height = image_height;

}

/**
 * @brief Set the width of the image to the jpeg structure
 * 
 * @param[in] jpg 
 * @param[in] image_width 
 */
void jpeg_set_image_width(struct jpeg *jpg, uint32_t image_width){

    jpg->width = image_width;

}

/**
 * @brief Set the number of color components to the jpeg structure
 * 
 * @param[in] jpg 
 * @param[in] nb_components 
 */
void jpeg_set_nb_components(struct jpeg *jpg, uint8_t nb_components){

    jpg->nb_component = nb_components;

}

/**
 * @brief Set the sampling factor for a given color component and a given direction to the jpeg structure
 * 
 * @param[in] jpg 
 * @param[in] cc 
 * @param[in] dir 
 * @param[in] sampling_factor 
 */
void jpeg_set_sampling_factor(struct jpeg *jpg, enum color_component cc, enum direction dir, uint8_t sampling_factor){

    jpg->sample[cc][dir] = sampling_factor;

}

/**
 * @brief Set the huffman table for a given color component and a given sample type to the jpeg structure
 * 
 * @param[in] jpg 
 * @param[in] acdc 
 * @param[in] cc 
 * @param[in] htable 
 */
void jpeg_set_huffman_table(struct jpeg *jpg, enum sample_type acdc, enum color_component cc, struct huff_table *htable){

    jpg->huff[cc][acdc] = htable;

}

/**
 * @brief Set the quantization table for a given color component to the jpeg structure
 * 
 * @param[in] jpg 
 * @param[in] cc 
 * @param[in] qtable 
 */
void jpeg_set_quantization_table(struct jpeg *jpg, enum color_component cc, uint8_t *qtable){

    jpg->qtable[cc] = qtable;

}

/**
 * @brief Write the header in a .jpg file from a jpeg structure
 * 
 * @param[in] jpg 
 */
void jpeg_write_header(struct jpeg *jpg){


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
        *pt = jpg->sample[i-1][0]*16 + jpg->sample[i-1][1];
        fwrite(pt, 1, 1, fg);
        *pt = (i == 1) ? 0 : 1;
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
    fwrite(pt, 1, 2, fg); 
    *pt = (uint16_t)jpg->nb_component;
    fwrite(pt, 1, 1, fg);
    for (uint16_t i = 1; i < jpg->nb_component + 1; i++){
        *pt  = i;
        fwrite(pt, 1, 1, fg);
        *pt = (((i == 1) ? 0:1)) + (((i == 1) ? 0:1))*16;
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

/**
 * @brief Write the footer in a .jpg file from a jpeg structure
 * 
 * @param[in] jpg 
 */
void jpeg_write_footer(struct jpeg *jpg){

    FILE *fg = fopen(jpg->out_filename, "ab");

    uint16_t val = 0xd9ff;
    uint16_t *pt = &val;
    fwrite(pt, 1, 2, fg);
    fclose(fg);

}

/**
 * @brief Creat a new bitstream from a jpeg structure
 * 
 * @param[in] jpg 
 * @return struct bitstream1* 
 */
struct bitstream *jpeg_get_bitstream(struct jpeg *jpg){

    struct bitstream *bitstream = bitstream_create(jpg->out_filename);
    return bitstream;

}

