#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <bloc.h>
#include <costable.h>

/**
 * @brief 
 * 
 */
struct frequential_bloc_t {
    struct frequential_bloc_t *next;
    int16_t matrice[8][8];
};

void frequential_bloc_set_next(struct frequential_bloc_t *frequential_bloc, struct frequential_bloc_t *next)
{
    frequential_bloc->next = next;
}

struct frequential_bloc_t* frequential_bloc_get_next(struct frequential_bloc_t *bloc)
{
    return bloc->next;
}

int16_t frequential_bloc_get_matrice(struct frequential_bloc_t *frequential_bloc, uint8_t i, uint8_t j){
    return frequential_bloc->matrice[i][j];
}


void frequential_bloc_add(struct frequential_bloc_t **bloc, struct frequential_bloc_t *next){
    struct frequential_bloc_t *tmp = *bloc;
    if (tmp == NULL){
        *bloc = next;
    } else {
        while (tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = next;
    }
}




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
            printf("%x ", bloc->matrice[i][j]);
        }
        printf("\n");
    }
}

void frequential_blocs_print(struct frequential_bloc_t *frequential_blocs){
    struct frequential_bloc_t *tmp = frequential_blocs;
    while (tmp != NULL){
        frequential_bloc_print(tmp);
        tmp = tmp->next;
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

// On améliore la fonction qui crée les coefficients de la DCT
// grâce à un tableau de produits des cosius créé sur python:

// import numpy as np

// MAT1 = np.zeros((8, 8))

// for i in range(8):
//     for j in range(8):
//         MAT1[i][j] = np.cos((2*i+1)*j*np.pi/16)

// MAT2 = np.zeros((64, 64))

// for i in range(8):
//     for x in range(8):
//         for j in range(8):
//             for y in range(8):
//                 MAT2[8*i+x][8*j+y] = MAT1[x][i] * MAT1[y][j]

// print("{")
// for i in range(8):
//     for x in range(8):
//         print("{")
//         for j in range(8):
            
//             for y in range(8):
//                 print(MAT2[8*i+x][j*8+y], end=", ")
            
//         print("},", end="\n")    
// print("}")

float coef_dct2(int16_t bloc_copy[8][8], uint32_t i, uint32_t j){

    float n = 8;
    float resultat = 0.0;
    for(uint32_t x = 0; x < 8; x++){
        for(uint32_t y = 0; y < 8 ; y++){
            //printf("%d", bloc_copy[x][y]);
            resultat += (float)(bloc_copy[x][y]) * costables[8*i+x][8*j+y];
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

struct frequential_bloc_t *dct(struct bloc_t *bloc){
    int16_t new_bloc[8][8];
    int16_t bloc_copy[8][8];
    for(uint32_t i=0; i<8; i++){
        for(uint32_t j=0; j<8; j++){
            bloc_copy[i][j] = bloc_get_matrice(bloc, i, j)-128;
        }
    }
    for(uint32_t i=0; i<8; i++){
        for(uint32_t j=0; j<8; j++){
            new_bloc[i][j] = (int16_t)coef_dct2(bloc_copy, i, j);
        }
    }
    struct frequential_bloc_t *blocc = frequential_bloc_create(new_bloc);
    return blocc;
}

