#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

struct frequential_bloc_t {
    struct frequential_bloc_t *next;
    int16_t matrice[8][8];
};

void frequential_blocs_destroy(struct frequential_bloc_t *frequential_blocs){
    struct frequential_bloc_t *tmp = frequential_blocs;
    while (tmp != NULL){
        struct frequential_bloc_t *tmp2 = tmp->next;
        free(tmp);
        tmp = tmp2;
    }
}

//faire le DCT ici

struct frequential_bloc_t *frequential_bloc_create(int16_t matrice[8][8]){
    struct frequential_bloc_t *bloc = calloc(1, sizeof(struct frequential_bloc_t));
    bloc->next = NULL;
    if (matrice != NULL){
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                //printf("%u\n", matrice[i][j]);
                bloc->matrice[i][j] = matrice[i][j];
            }
        }
    } else {
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                bloc->matrice[i][j] = 0;
            }
        }
    }
    return bloc;
}

void frequential_bloc_print(struct frequential_bloc_t *bloc){
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%i ", bloc->matrice[i][j]);
        }
        printf("\n");
    }
}

float coef_dct(int16_t bloc_copy[8][8], uint32_t i, uint32_t j){
    float pi = 3.14159265358;/*9793238462643383279502884197169399375105820;*/
    float n = 8;
    float resultat = 0.0;
    for(uint32_t x = 0; x < 8; x++){
        for(uint32_t y = 0; y < 8 ; y++){
            //printf("%d", bloc_copy[x][y]);
            resultat += (float)(bloc_copy[x][y]) * cosf(((2*(float)(x)+1)*(float)(i)*pi)/((float)(2*n))) * cosf(((2*(float)(y)+1)*(float)j*pi)/((float)(2*n))); 
        }
    }
    if(i==0 && j==0){
        resultat *= (2/n) * 1/2; 
    }
    else if(i==0){
        resultat *= (2/n) * 1/sqrt(2);
    }
    else if(j==0){
        resultat *= (2/n) * 1/sqrt(2); 
    }
    else{
        resultat *= (2/n);
    }
    return resultat;
}


struct frequential_bloc_t *dct(uint8_t bloc[8][8]){
    int16_t new_bloc[8][8];
    int16_t bloc_copy[8][8];
    for(uint32_t i=0; i<8; i++){
        for(uint32_t j=0; j<8; j++){
            bloc_copy[i][j] = bloc[i][j];
        }
    }
    for(uint32_t i=0; i<8; i++){
        for(uint32_t j=0; j<8; j++){
            new_bloc[i][j] = (int16_t)coef_dct(bloc_copy, i, j);
        }
    }
    struct frequential_bloc_t *blocc = frequential_bloc_create(new_bloc);
    return blocc;
}
