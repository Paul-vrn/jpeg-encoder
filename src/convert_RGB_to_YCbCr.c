/**
 * @file convert_RGB_to_YCbCr.c
 * @author Paul Vernin (paul.vernin@grenoble-inp.org)
 * @brief file containing the functions to convert RGB to YCbCr
 * @version 1.0
 * @date 2022-05-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/**
 * @brief Convert an RGB matrix to YCbCr matrix
 * @test✔️ (valeurs approximatives)
 * @param[in] matrice The RGB matrix
 * @param[in] height The height of the matrix
 * @param[in] width The width of the matrix
 */
void convert_RGB_to_YCbCr(uint8_t ***matrice, uint32_t height, uint32_t width){
    if (matrice[1] == NULL && matrice[2] == NULL){
        return;
    } 
    for (uint32_t i = 0; i < height; i++){
        for (uint32_t j = 0; j < width; j++){
            double R = (double)matrice[0][i][j];
            double G = (double)matrice[1][i][j];
            double B = (double)matrice[2][i][j];
            double Y = ((0.299 * R) + (0.587 * G) + (0.114 * B));
            double Cb = ((-0.1687 * R) + (-0.3313 * G) + (0.5 * B) + 128);
            double Cr = ((0.5 * R) + (-0.4187 * G) + (-0.0813 * B) + 128);
            matrice[0][i][j] = (uint8_t) Y;
            matrice[1][i][j] = (uint8_t) Cb;
            matrice[2][i][j] = (uint8_t) Cr;
        }
    }
}
