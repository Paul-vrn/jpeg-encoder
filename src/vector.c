#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "htables.h"
#include "qtables.h"
#include "frequential_bloc.h"

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b)) 

struct vector_t {
    struct vector_t *next;
    int16_t vector[64];
};

int16_t vector_get(struct vector_t *vector, uint32_t index)
{
    return vector->vector[index];
}
struct vector_t *vector_get_next(struct vector_t *vector)
{
    return vector->next;
}

struct vector_t* create_vector(int16_t tab[64]){
    struct vector_t *vector = calloc(1, sizeof(struct vector_t));
    for (int i = 0; i < 64; i++){
        vector->vector[i] = tab[i];
    }
    vector->next = NULL;
    return vector;
}

void vector_print(struct vector_t *vector){
    for (int i = 0; i < 64; i++) {
        printf("%x ", vector->vector[i]);
        if (i % 8 == 7) {
            printf("\n");
        }
    }
}

/**
 * @brief Create a vector from bloc object
 * 
 * @param freq_bloc 
 * @return struct vector_t* 
 *//*
struct vector_t *create_vector_from_bloc(struct frequential_bloc_t *freq_bloc){   //On a utilisé la fonction d'un autre groupe la notre ne marchait pas merci Arthur Lebeurrier
    struct vector_t* vector = calloc(1, sizeof(struct vector_t));
    vector->next = NULL;    
    int cpt = 0;
    for (int i = 0; i<14; i++){
        if (i%2 == 0){
            for (int j = max(0, i-7); j<=min(i,7); j++){
                vector->vector[cpt] = frequential_bloc_get_matrice(freq_bloc, i-j, j);
                cpt++;
            }
        } else {
            for (int j = max(0, i-7); j<=min(i,7); j++){
                vector->vector[cpt] = frequential_bloc_get_matrice(freq_bloc, j, i-j);
                cpt++;
            }
        }
    }
    return vector;
}*/
struct vector_t *create_vector_from_bloc(struct frequential_bloc_t *freq_bloc){ 
    struct vector_t* Vvector = calloc(1, sizeof(struct vector_t));
    Vvector->next = NULL; 
    for (int j = 0; j < 8; j++){
        for (int i = 0; i < 8; i++){
            if ((((i+j) % 2) == 0) && ((i+j) < 8)){
                Vvector->vector[(i+(((i+j+1)*(i+j))/2))] = frequential_bloc_get_matrice(freq_bloc, j, i);
            } 
            else if ((((i+j) % 2) == 1) && ((i+j) < 8)){
                Vvector->vector[(j+(((i+j+1)*(i+j))/2))] = frequential_bloc_get_matrice(freq_bloc, j, i);
            }
            else if((((i+j) % 2) == 0) && ((i+j) >= 8)){
                Vvector->vector[(63-((7-i)+(((7-i)+(7-j)+1)*((7-i)+(7-j)))/2))] = frequential_bloc_get_matrice(freq_bloc, j, i);
            }
            else if ((((i+j) % 2) == 1) && ((i+j) >= 8)){
                Vvector->vector[(63-((7-j)+(((7-i)+(7-j)+1)*((7-i)+(7-j)))/2))] = frequential_bloc_get_matrice(freq_bloc, j, i);
            }
        }
    }
    return Vvector;
}

/**
 * @brief
 * @test❌ (valeur approximative)
 * @param vector 
 */
void vector_quantificationY(struct vector_t *vector){
    for (uint8_t i = 0; i < 64; i++){
        vector->vector[i] = (int16_t) round(vector->vector[i] / quantification_table_Y[i]);
    }
}

/**
 * @brief
 * @test❌ (valeur approximative)
 * @param vector 
 */
void vector_quantificationCbCr(struct vector_t *vector){
    for (uint8_t i = 0; i < 64; i++){
        vector->vector[i] = (int16_t) (vector->vector[i] / quantification_table_CbCr[i]);
    }
}

void vectors_quantificationY(struct vector_t *vectors){
    struct vector_t *tmp = vectors;
    while (tmp != NULL){
        vector_quantificationY(tmp);
        tmp = tmp->next;
    }
}

void vectors_quantificationCbCr(struct vector_t *vectors){
    struct vector_t *tmp = vectors;
    while (tmp != NULL){
        vector_quantificationCbCr(tmp);
        tmp = tmp->next;
    }
}

/**
 * @brief
 * @test✔️
 * @param vector 
 */
void vectors_destroy(struct vector_t *vector){
    struct vector_t *tmp = vector;
    while (tmp != NULL){
        struct vector_t *tmp2 = tmp->next;
        free(tmp);
        tmp = tmp2;
    }
    vector = NULL;
}
