#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/*
  Convertit une matrice de pixels en RGB en matrices de pixels en YCbCr
*/

void ConversionYCbCr(uint8_t**matrice, uint32_t hauteur, uint32_t longueur){
    uint8_t GRIS = 0;
    if (GRIS){
        return;
    } else {
    for(uint32_t i=0; i < hauteur; i++){
        for(uint32_t j=0; j < longueur; j += 3){
            uint32_t R = matrice[i][j];
            uint32_t G = matrice[i][j+1];
            uint32_t B = matrice[i][j+2];
            uint32_t Y = 0.299 * R + 0.587 * G + 0.114 * B;
            uint32_t Cb = -0.1687 * R + -0.3313 * G + 0.5 * B;
            uint32_t Cr = 0.5 * R -0.4187 * G -0.0813 * B;
            matrice[i][j] = Y;
            matrice[i][j+1] = Cb;
            matrice[i][j+2] = Cr;
        }
    }
    }
    return NULL;
}


