#ifndef JPEG_WRITER_H_
#define JPEG_WRITER_H_

#include <stdint.h>
#include "huffman.h"

/********************/
/* Types de données */
/********************/

/* Type énuméré représentant les composantes de couleur YCbCr. */
enum color_component
{
    Y,
    Cb,
    Cr,
    NB_COLOR_COMPONENTS
};

/*
    Type énuméré représentant les types de composantes fréquentielles (DC ou AC).
*/
enum sample_type
{
    DC,
    AC,
    NB_SAMPLE_TYPES
};

/*
    Type énuméré représentant la direction des facteurs d'échantillonnage (H
    pour horizontal, V pour vertical).
*/
enum direction
{
    H,
    V,
    NB_DIRECTIONS
};

/*
    Strucuture contenant toute les information pour écrire l'entête jpeg
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



/***********************************************/
/* Ouverture, fermeture et fonctions générales */
/***********************************************/

/* Alloue et retourne une nouvelle structure jpeg. */
struct jpeg *jpeg_create(void);

/*
    Détruit une structure jpeg. 
    Toute la mémoire qui lui est associée est libérée.
*/
void jpeg_destroy(struct jpeg *jpg);

/*
    Ecrit l'entête jpeg a partir des paramètre présent dans la strucuture jpeg
*/

void jpeg_write_header(struct jpeg *jpg);

/* 
    Ecrit le marqueur de fin du fichier jpeg
*/

void jpeg_write_footer(struct jpeg *jpg);


/****************************************************/
/* Gestion des paramètres de l'encodeur via le jpeg */
/****************************************************/

/* Ecrit le nom de fichier PPM ppm_filename dans la structure jpeg. */
void jpeg_set_ppm_filename(struct jpeg *jpg,
                                  const char *ppm_filename);

/* Ecrit le nom du fichier de sortie jpeg_filename dans la structure jpeg. */
void jpeg_set_jpeg_filename(struct jpeg *jpg,
                                   const char *jpeg_filename);



/*
    Ecrit la hauteur de l'image traitée, en nombre de pixels,
    dans la structure jpeg.
*/
void jpeg_set_image_height(struct jpeg *jpg,
                                  uint32_t image_height);


/*
    Ecrit la largeur de l'image traitée, en nombre de pixels,
    dans la structure jpeg.
*/
void jpeg_set_image_width(struct jpeg *jpg,
                                 uint32_t image_width);



/*
    Ecrit le nombre de composantes de couleur de l'image traitée
    dans la structure jpeg.
*/
void jpeg_set_nb_components(struct jpeg *jpg,
                                   uint8_t nb_components);


/*
    Ecrit dans la structure jpeg le facteur d'échantillonnage 
    sampling_factor
    à utiliser pour la composante de couleur cc et la direction dir.
*/
void jpeg_set_sampling_factor(struct jpeg *jpg,
                                     enum color_component cc,
                                     enum direction dir,
                                     uint8_t sampling_factor);


/*
    Ecrit dans la structure jpeg la table de Huffman huff_table à utiliser
    pour encoder les données de la composante fréquentielle acdc, pour la
    composante de couleur cc.
*/
void jpeg_set_huffman_table(struct jpeg *jpg,
                                   enum sample_type acdc,
                                   enum color_component cc,
                                   struct huff_table *htable);



/*
    Ecrit dans la structure jpeg la table de quantification à utiliser
    pour compresser les coefficients de la composante de couleur cc.
*/
void jpeg_set_quantization_table(struct jpeg *jpg,
                                        enum color_component cc,
                                        uint8_t *qtable);

/*

*/
struct bitstream1 *jpeg_get_bitstream(struct jpeg *jpg);

#endif /* JPEG_WRITER_H_ */
