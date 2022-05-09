#include <huffman.h>
#include <htables.h>
#include <stdio.h>
#include <string.h>
#include <qtables.h>
#include <stdint.h>



int main(void){

    uint32_t height = 8;
    uint32_t width = 8;

    uint8_t H1 = 1;
    uint8_t H2 = 1;
    uint8_t H3 = 1;
    uint8_t V1 = 1;
    uint8_t V2 = 1;
    uint8_t V3 = 1;
    char filename_out[] = "test.jpg";
    char filename[] = "../images/invader.pgm";

    struct jpeg *jpeg = jpeg_create();
    //On rentre les paramètre dans la structure entete set_XXX
    // Caractèristique de l'image à traiter
    jpeg_set_ppm_filename(jpeg, filename);
    jpeg_set_jpeg_filename(jpeg, filename_out);
    jpeg_set_image_width(jpeg, width);
    jpeg_set_image_height(jpeg, height);



    jpeg_set_nb_components(jpeg, 1);
    jpeg_set_sampling_factor(jpeg, Y, H, H1);
    jpeg_set_sampling_factor(jpeg, Y, V, V1);
    struct huff_table *htable_DC_Y = huffman_table_build(htables_nb_symb_per_lengths[DC][Y], htables_symbols[DC][Y], htables_nb_symbols[DC][Y]);
    jpeg_set_huffman_table(jpeg, DC, Y, htable_DC_Y);
    struct huff_table *htable_AC_Y = huffman_table_build(htables_nb_symb_per_lengths[AC][Y], htables_symbols[AC][Y], htables_nb_symbols[AC][Y]);
    jpeg_set_huffman_table(jpeg, AC, Y, htable_AC_Y);
    jpeg_set_quantization_table(jpeg, Y, quantification_table_Y);

    jpeg_write_header(jpeg);







    return 0;
}