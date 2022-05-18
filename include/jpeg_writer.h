#ifndef JPEG_WRITER_H_
#define JPEG_WRITER_H_

#include <stdint.h>
#include "huffman.h"



/**
 * @brief An Enumerated type describing the differents color types
 * 
 */
enum color_component
{
    Y,
    Cb,
    Cr,
    NB_COLOR_COMPONENTS
};

/**
 * @brief An enumerated type descriping the differents sample types
 * 
 */
enum sample_type
{
    DC,
    AC,
    NB_SAMPLE_TYPES
};

/**
 * @brief An enumerated type describing the differents types of sampling factors
 * 
 */
enum direction
{
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
struct jpeg *jpeg_create(void);

/**
 * @brief Destroy and free a jpeg structure
 * 
 * @param jpg 
 */
void jpeg_destroy(struct jpeg *jpg);

/**
 * @brief Write the header in a .jpg file from a jpeg structure
 * 
 * @param jpg 
 */
void jpeg_write_header(struct jpeg *jpg);

/**
 * @brief Write the footer in a .jpg file from a jpeg structure
 * 
 * @param jpg 
 */
void jpeg_write_footer(struct jpeg *jpg);


/**
 * @brief Add the filname of the inpute ppm file to the jpeg structure
 * 
 * @param jpg 
 */ 
void jpeg_set_ppm_filename(struct jpeg *jpg,
                                  const char *ppm_filename);


/**
 * @brief Add the filename of the outpute jpeg file to the jpeg structure
 * 
 * @param jpg 
 * @param jpeg_filename 
 */
void jpeg_set_jpeg_filename(struct jpeg *jpg,
                                   const char *jpeg_filename);



/**
 * @brief Set the height of the image to the jpeg structure
 * 
 * @param jpg 
 * @param image_height 
 */
void jpeg_set_image_height(struct jpeg *jpg,
                                  uint32_t image_height);


/**
 * @brief Set the width of the image to the jpeg structure
 * 
 * @param jpg 
 * @param image_width 
 */
void jpeg_set_image_width(struct jpeg *jpg,
                                 uint32_t image_width);



/**
 * @brief Set the number of color components to the jpeg structure
 * 
 * @param jpg 
 * @param nb_components 
 */
void jpeg_set_nb_components(struct jpeg *jpg,
                                   uint8_t nb_components);


/**
 * @brief Set the sampling factor for a given color component and a given direction to the jpeg structure
 * 
 * @param jpg 
 * @param cc 
 * @param dir 
 * @param sampling_factor 
 */
void jpeg_set_sampling_factor(struct jpeg *jpg,
                                     enum color_component cc,
                                     enum direction dir,
                                     uint8_t sampling_factor);


/**
 * @brief Set the huffman table for a given color component and a given sample type to the jpeg structure
 * 
 * @param jpg 
 * @param acdc 
 * @param cc 
 * @param htable 
 */
void jpeg_set_huffman_table(struct jpeg *jpg,
                                   enum sample_type acdc,
                                   enum color_component cc,
                                   struct huff_table *htable);



/**
 * @brief Set the quantization table for a given color component to the jpeg structure
 * 
 * @param jpg 
 * @param cc 
 * @param qtable 
 */
void jpeg_set_quantization_table(struct jpeg *jpg,
                                        enum color_component cc,
                                        uint8_t *qtable);


/**
 * @brief Creat a new bitstream from a jpeg structure
 * 
 * @param jpg 
 * @return struct bitstream1* 
 */
struct bitstream1 *jpeg_get_bitstream(struct jpeg *jpg);

#endif /* JPEG_WRITER_H_ */
