#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "jpeg_writer.h"
#include <stdbool.h>
#include "read_param.h"
#include "read_pic.h"
#include "convert_RGB_to_YCbCr.h"
#include "jpeg_writer.h"
#include "mcu.h"
#include "htables.h"
#include "huffman.h"
#include "qtables.h"
#include "bitstream.h"


int main(int argc, char *argv[])
{
    uint32_t height = 0;
    uint32_t width = 0;
    uint8_t type;

    uint8_t H1 = 2;
    uint8_t H2 = 2;
    uint8_t H3 = 2;
    uint8_t V1 = 2;
    uint8_t V2 = 2;
    uint8_t V3 = 2;
    char *filename_out;
    char *filename;

    read_param(argc, argv, &H1, &V1, &H2, &V2, &H3, &V3, &filename_out, &filename);

    uint8_t ***matrice = creat_matrix(&height, &width, &type, &filename);
    // lecture  des paramètres
    // Lecture des fichiers


    struct jpeg *jpeg = jpeg_create();

    /* ------ SET HEADER JPEG ------ */

    jpeg_set_ppm_filename(jpeg, filename);
    jpeg_set_jpeg_filename(jpeg, filename_out);
    jpeg_set_image_width(jpeg, width);
    jpeg_set_image_height(jpeg, height);

    if (type == 5){

        jpeg_set_nb_components(jpeg, 1);
        jpeg_set_sampling_factor(jpeg, Y, H, H1);
        jpeg_set_sampling_factor(jpeg, Y, V, V1);
        struct huff_table *htable_DC_Y = huffman_table_build(htables_nb_symb_per_lengths[DC][Y], htables_symbols[DC][Y], htables_nb_symbols[DC][Y]);
        jpeg_set_huffman_table(jpeg, DC, Y, htable_DC_Y);
        struct huff_table *htable_AC_Y = huffman_table_build(htables_nb_symb_per_lengths[AC][Y], htables_symbols[AC][Y], htables_nb_symbols[AC][Y]);
        jpeg_set_huffman_table(jpeg, AC, Y, htable_AC_Y);
 
        jpeg_set_quantization_table(jpeg, Y, quantification_table_Y);

    } else if (type == 6){

        jpeg_set_nb_components(jpeg, 3);

        jpeg_set_sampling_factor(jpeg, Y, H, H1);
        jpeg_set_sampling_factor(jpeg, Y, V, V1);
        jpeg_set_sampling_factor(jpeg, Cb, H, H2);
        jpeg_set_sampling_factor(jpeg, Cb, V, V2);
        jpeg_set_sampling_factor(jpeg, Cr, H, H3);
        jpeg_set_sampling_factor(jpeg, Cr, V, V3);

        struct huff_table *htable_DC_Y = huffman_table_build(htables_nb_symb_per_lengths[DC][Y], htables_symbols[DC][Y], htables_nb_symbols[DC][Y]);
        jpeg_set_huffman_table(jpeg, DC, Y, htable_DC_Y);
        struct huff_table *htable_AC_Y = huffman_table_build(htables_nb_symb_per_lengths[AC][Y], htables_symbols[AC][Y], htables_nb_symbols[AC][Y]);
        jpeg_set_huffman_table(jpeg, AC, Y, htable_AC_Y);

        struct huff_table *htable_DC_Cb = huffman_table_build(htables_nb_symb_per_lengths[DC][Cb], htables_symbols[DC][Cb], htables_nb_symbols[DC][Cb]);
        jpeg_set_huffman_table(jpeg, DC, Cb, htable_DC_Cb);
        struct huff_table *htable_AC_Cb = huffman_table_build(htables_nb_symb_per_lengths[AC][Cb], htables_symbols[AC][Cb], htables_nb_symbols[AC][Cb]);
        jpeg_set_huffman_table(jpeg, AC, Cb, htable_AC_Cb);

        struct huff_table *htable_DC_Cr = huffman_table_build(htables_nb_symb_per_lengths[DC][Cr], htables_symbols[DC][Cr], htables_nb_symbols[DC][Cr]);
        jpeg_set_huffman_table(jpeg, DC, Cr, htable_DC_Cr);
        struct huff_table *htable_AC_Cr = huffman_table_build(htables_nb_symb_per_lengths[AC][Cr], htables_symbols[AC][Cr], htables_nb_symbols[AC][Cr]);
        jpeg_set_huffman_table(jpeg, AC, Cr, htable_AC_Cr);

        jpeg_set_quantization_table(jpeg, Y, quantification_table_Y);
        jpeg_set_quantization_table(jpeg, Cb, quantification_table_CbCr);
        jpeg_set_quantization_table(jpeg, Cr, quantification_table_CbCr);

    }
    jpeg_write_header(jpeg);

    printf("----- CONVERT RGB TO YCbCr -----\n");
    convert_RGB_to_YCbCr(matrice, height, width);

    printf("----- CREATE MCUS -----\n");
    struct mcu_t *mcu = decoupage_mcu(matrice, height, width, H1, H2, H3, V1, V2, V3);
    //mcu_print(mcu_get_by_id(mcu, 12));
    
    printf("----- SOUS ECHANTILLONAGE ------\n");
    mcus_sous_echantillonne(mcu);
    //mcu_print(mcu_get_by_id(mcu, 12));


    printf("----- TRANSFORMATION DCT ------\n");
    mcu_dct(mcu);
    // mcu_print(mcu);

    printf("----- ZIG ZAG ------\n");
    mcu_zigzag(mcu);
    // mcu_print(mcu);

    printf("----- QUANTIFICATION ------\n");
    mcu_quantification(mcu);
    //mcu_print(mcu_get_by_id(mcu, 12));


    printf("----- ENCODAGE ------\n");
    mcu_encode(jpeg_get_bitstream(jpeg), mcu);
    
    jpeg_write_footer(jpeg); 
    
    return EXIT_SUCCESS;
}
