#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "read_param.h"
#include "read_pic.h"

int main(int argc, char *argv[])
{
    uint32_t height = 0;
    uint32_t width = 0;
    uint8_t type;

    uint8_t H1 = 1;
    uint8_t H2 = 1;
    uint8_t H3 = 1;
    uint8_t V1 = 1;
    uint8_t V2 = 1;
    uint8_t V3 = 1;
    char *filename_out;
    char *filename;

    read_param(argc, argv, &H1, &V1, &H2, &V2, &H3, &V3, &filename_out, &filename);

    uint8_t ***matr = creat_matrix(&height, &width, &type, &filename);
    //lecture  des paramètres
    //Lecture des fichiers


    struct jpeg *jpg = jpeg_create();

    jpeg_set_ppm_filename(jpg, filename);
    jpeg_set_jpeg_filename(jpg, filename_out);
    jpeg_set_image_width(jpg, width);
    jpeg_set_image_height(jpg, height);

/*
    ici on fait des trucs super pour appeler les autres
    jpeg_set_XXX avec les arguments qui vont bien.
*/
    jpeg_set_nb_components(jpg, 3); // 1 si gris, 3 si couleur
    jpeg_write_header(jpg);

    /* Et là des trucs géniaux, comment encoder une image ... */
    //crée les MCUS, faire les transformations, etc...
    
    struct bitstream *bs = jpeg_get_bitstream(jpg);

    /* Voilà, on finit proprement notre belle image! */
    jpeg_write_footer(jpg); 

    
    return EXIT_SUCCESS;
}
