#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/**
 * @brief Convert an RGB matrix to YCbCr matrix
 * @test❌ (valeurs approximatives différente de -1)
 * @param matrice The RGB matrix
 * @param height The height of the matrix
 * @param width The width of the matrix
 */
void convert_RGB_to_YCbCr(uint8_t ***matrice, uint32_t height, uint32_t width){
    if (matrice[1] == NULL && matrice[2] == NULL){
        return;
    } 
    printf("test\n");
    for (uint32_t i = 0; i < height; i++){
        for (uint32_t j = 0; j < width; j++){
            uint8_t R = (uint8_t)matrice[0][i][j];
            uint8_t G = (uint8_t)matrice[1][i][j];
            uint8_t B = (uint8_t)matrice[2][i][j];
            uint8_t Y = (uint8_t)((0.299 * R) + (0.587 * G) + (0.114 * B));
            uint8_t Cb = (uint8_t)((-0.1687 * R) + (-0.3313 * G) + (0.5 * B) + 128);
            uint8_t Cr = (uint8_t)((0.5 * R) + (-0.4187 * G) + (-0.0813 * B) + 128);
            matrice[0][i][j] = Y;
            matrice[1][i][j] = Cb;
            matrice[2][i][j] = Cr;
        }
    }
}
