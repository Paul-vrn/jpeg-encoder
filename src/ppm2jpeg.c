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


    struct jpeg *jpg = jpeg_create();

    /* ------ SET HEADER JPEG ------ */

    jpeg_set_ppm_filename(jpg, filename);
    jpeg_set_jpeg_filename(jpg, filename_out);
    jpeg_set_image_width(jpg, width);
    jpeg_set_image_height(jpg, height);

    if (type == 5){

        jpeg_set_nb_components(jpg, 1);
        jpeg_set_sampling_factor(jpg, Y, H, H1);
        jpeg_set_sampling_factor(jpg, Y, V, V1);
        struct huff_table *htable_DC_Y = huffman_table_build(htables_nb_symb_per_lengths[DC][Y], htables_symbols[DC][Y], htables_nb_symbols[DC][Y]);
        jpeg_set_huffman_table(jpg, DC, Y, htable_DC_Y);
        struct huff_table *htable_AC_Y = huffman_table_build(htables_nb_symb_per_lengths[AC][Y], htables_symbols[AC][Y], htables_nb_symbols[AC][Y]);
        jpeg_set_huffman_table(jpg, AC, Y, htable_AC_Y);
 
        jpeg_set_quantization_table(jpg, Y, quantification_table_Y);

    } else if (type == 6){

        jpeg_set_nb_components(jpg, 3);

        jpeg_set_sampling_factor(jpg, Y, H, H1);
        jpeg_set_sampling_factor(jpg, Y, V, V1);
        jpeg_set_sampling_factor(jpg, Cb, H, H2);
        jpeg_set_sampling_factor(jpg, Cb, V, V2);
        jpeg_set_sampling_factor(jpg, Cr, H, H3);

        jpeg_set_sampling_factor(jpg, Cr, V, V3);
        struct huff_table *htable_DC_Y = huffman_table_build(htables_nb_symb_per_lengths[DC][Y], htables_symbols[DC][Y], htables_nb_symbols[DC][Y]);
        jpeg_set_huffman_table(jpg, DC, Y, htable_DC_Y);
        struct huff_table *htable_AC_Y = huffman_table_build(htables_nb_symb_per_lengths[AC][Y], htables_symbols[AC][Y], htables_nb_symbols[AC][Y]);
        jpeg_set_huffman_table(jpg, AC, Y, htable_AC_Y);

        struct huff_table *htable_DC_Cr = huffman_table_build(htables_nb_symb_per_lengths[DC][Cr], htables_symbols[DC][Cr], htables_nb_symbols[DC][Cr]);
        jpeg_set_huffman_table(jpg, DC, Cr, htable_DC_Cr);
        struct huff_table *htable_AC_Cr = huffman_table_build(htables_nb_symb_per_lengths[AC][Cr], htables_symbols[AC][Cr], htables_nb_symbols[AC][Cr]);
        jpeg_set_huffman_table(jpg, AC, Cr, htable_AC_Cr);

        struct huff_table *htable_DC_Cb = huffman_table_build(htables_nb_symb_per_lengths[DC][Cb], htables_symbols[DC][Cb], htables_nb_symbols[DC][Cb]);
        jpeg_set_huffman_table(jpg, DC, Cb, htable_DC_Cb);
        struct huff_table *htable_AC_Cb = huffman_table_build(htables_nb_symb_per_lengths[AC][Cb], htables_symbols[AC][Cb], htables_nb_symbols[AC][Cb]);
        jpeg_set_huffman_table(jpg, AC, Cb, htable_AC_Cb);

        jpeg_set_quantization_table(jpg, Y, quantification_table_Y);
        jpeg_set_quantization_table(jpg, Cb, quantification_table_CbCr);
        jpeg_set_quantization_table(jpg, Cr, quantification_table_CbCr);

    }
    jpeg_write_header(jpg);

    /* Et là des trucs géniaux, comment encoder une image ... */
    //crée les MCUS, faire les transformations, etc...

    /* ------ CONVERT RGB TO YCbCr ------ */
    convert_RGB_to_YCbCr(matrice, height, width);

    /* ------ CREATE MCUS ------ */
    struct mcu_t *mcu = decoupage_mcu(matrice, height, width, H1*V1, H2*V2, H3*V3);

    /* ------ SOUS ECHANTILLONAGE DES MCUS ------ */
    mcu_sous_echantillonne(mcu);

    /* ------ TRANSFORMATION DCT ------ */


    /* ------ ZIG ZAG ------ */


    /* ------ QUANTIFICATION ------ */


    /* ------ ENCODAGE DANS LE BITSTREAM ------ */

    struct bitstream *bitstream = bitstream_create(filename_out);
    



    


    jpeg_write_footer(jpg); 

    
    return EXIT_SUCCESS;
}
