#include <stdlib.h>
#include <stdio.h>

/*
  Convertit une matrice de pixels en RGB en matrices de pixels en YCbCr
*/
/*
void ConversionYCbCr(*matrice,hauteur,longueur){
    for(i=0; i < hauteur; i++){
        for(j=0; j < longueur){
            R = *matrice[i][j][0]
            G = *matrice[i][j][1] 
            B = *matrice[i][j][2]
            Y = 0,299 * R + 0,587 * G + 0,114 * B
            Cb = -0,1687 * R + -0,3313 * G + 0,5 * B
            Cr = 0,5 * R -0,4187 * G -0,0813 * B
            *matrice[i][j][0] = Y
            *matrice[i][j][1] = Cb
            *matrice[i][j][2] = Cr
        }

    }

}

*/