/**
 * @file ppm2jpeg.c
 * @author team 18
 * @brief main function of the program
 * @version 1.0
 * @date 2022-05-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
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
// #include "huffman.h"


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
	char *filename_out = NULL;
	char *filename = NULL;

	read_param(argc, argv, &H1, &V1, &H2, &V2, &H3, &V3, &filename_out, &filename);

	uint8_t ***matrice = creat_matrix(&height, &width, &type, &filename);

    struct jpeg *jpeg = jpeg_create();

	/* ------ SET HEADER JPEG ------ */

    jpeg_set_ppm_filename(jpeg, filename);
    jpeg_set_jpeg_filename(jpeg, filename_out);
    jpeg_set_image_width(jpeg, width);
    jpeg_set_image_height(jpeg, height);


    struct huff_table *ht_DC_Y = huffman_table_build(htables_nb_symb_per_lengths[DC][Y], htables_symbols[DC][Y], htables_nb_symbols[DC][Y]);
	struct huff_table *ht_AC_Y = huffman_table_build(htables_nb_symb_per_lengths[AC][Y], htables_symbols[AC][Y], htables_nb_symbols[AC][Y]);
	struct huff_table *ht_DC_Cb = NULL;
	struct huff_table *ht_AC_Cb = NULL;
	struct huff_table *ht_DC_Cr = NULL;
	struct huff_table *ht_AC_Cr = NULL;

	if (type == 5){

		jpeg_set_nb_components(jpeg, 1);
		jpeg_set_sampling_factor(jpeg, Y, H, H1);
		jpeg_set_sampling_factor(jpeg, Y, V, V1);
		jpeg_set_huffman_table(jpeg, DC, Y, ht_DC_Y);
		jpeg_set_huffman_table(jpeg, AC, Y, ht_AC_Y);
 
		jpeg_set_quantization_table(jpeg, Y, quantification_table_Y);

	} else if (type == 6){

		jpeg_set_nb_components(jpeg, 3);

		jpeg_set_sampling_factor(jpeg, Y, H, H1);
		jpeg_set_sampling_factor(jpeg, Y, V, V1);
		jpeg_set_sampling_factor(jpeg, Cb, H, H2);
		jpeg_set_sampling_factor(jpeg, Cb, V, V2);
		jpeg_set_sampling_factor(jpeg, Cr, H, H3);
		jpeg_set_sampling_factor(jpeg, Cr, V, V3);

		jpeg_set_huffman_table(jpeg, DC, Y, ht_DC_Y);
		jpeg_set_huffman_table(jpeg, AC, Y, ht_AC_Y);

		ht_DC_Cb = huffman_table_build(htables_nb_symb_per_lengths[DC][Cb], htables_symbols[DC][Cb], htables_nb_symbols[DC][Cb]);
		jpeg_set_huffman_table(jpeg, DC, Cb, ht_DC_Cb);
		ht_AC_Cb = huffman_table_build(htables_nb_symb_per_lengths[AC][Cb], htables_symbols[AC][Cb], htables_nb_symbols[AC][Cb]);
		jpeg_set_huffman_table(jpeg, AC, Cb, ht_AC_Cb);

        ht_DC_Cr = huffman_table_build(htables_nb_symb_per_lengths[DC][Cr], htables_symbols[DC][Cr], htables_nb_symbols[DC][Cr]);
		jpeg_set_huffman_table(jpeg, DC, Cr, ht_DC_Cr);
        ht_AC_Cr = huffman_table_build(htables_nb_symb_per_lengths[AC][Cr], htables_symbols[AC][Cr], htables_nb_symbols[AC][Cr]);
		jpeg_set_huffman_table(jpeg, AC, Cr, ht_AC_Cr);

		jpeg_set_quantization_table(jpeg, Y, quantification_table_Y);
		jpeg_set_quantization_table(jpeg, Cb, quantification_table_CbCr);
		jpeg_set_quantization_table(jpeg, Cr, quantification_table_CbCr);

	}
	jpeg_write_header(jpeg);

	/* ------ CONVERT RGB TO YCbCr ------ */
	convert_RGB_to_YCbCr(matrice, height, width);

	/* ------ CREATE MCU ------ */
	struct mcu_t *mcu = decoupage_mcu(matrice, height, width, H1, V1);
	free_matrix(matrice);

	/* ------ DOWNSAMPLING ------ */
	mcus_downsampling(mcu, H1, V1, H2, V2, H3, V3);

	/* ------ DCT ------ */
	mcu_dct(mcu);

	/* ------ ZIG ZAG ------ */
	mcu_zigzag(mcu);

	/* ------ QUANTIFICATION ------ */
	mcu_quantification(mcu);

	/* ------ ENCODING ------ */
    struct bitstream *stream = bitstream_create(filename_out);
	mcu_encode(stream, mcu, ht_DC_Y, ht_AC_Y, ht_DC_Cb, ht_AC_Cb);
    bitstream_flush(stream);
    bitstream_destroy(stream);

	jpeg_write_footer(jpeg); 	

	/* ------ FREE MEMORY ------ */
	
	if (ht_DC_Y != NULL)
		huffman_table_destroy(ht_DC_Y);
	if (ht_AC_Y != NULL)
		huffman_table_destroy(ht_AC_Y);
	if (ht_DC_Cb != NULL)
		huffman_table_destroy(ht_DC_Cb);
	if (ht_AC_Cb != NULL)
		huffman_table_destroy(ht_AC_Cb);
	if (ht_DC_Cr != NULL)
		huffman_table_destroy(ht_DC_Cr);
	if (ht_AC_Cr != NULL)
		huffman_table_destroy(ht_AC_Cr);


	free(filename);
	if (filename_out != NULL)
		free(filename_out);
	mcus_destroy(&mcu);
	jpeg_destroy(jpeg);
	
	return EXIT_SUCCESS;
}
