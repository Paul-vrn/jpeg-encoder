#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "htables.h"
#include "qtables.h"
#include "frequential_bloc.h"

struct vector_t {
    struct vector_t *next;
    int16_t vector[64];
};

int16_t vector_get(struct vector_t *vector, uint32_t index)
{
    return vector->vector[index];
}

struct vector_t* create_vector(int16_t tab[64]){
    struct vector_t *vector = calloc(1, sizeof(struct vector_t));
    for (int i = 0; i < 64; i++){
        vector->vector[i] = tab[i];
    }
    vector->next = NULL;
    return vector;
}

/**
 * @brief create a new vector from a bloc by zig zag
 * 
*/
struct vector_t* create_vector_from_bloc(struct frequential_bloc_t *freq_bloc){
    struct vector_t* vector = calloc(1, sizeof(struct vector_t));
    vector->next = NULL;
    /* TODO: à changer pour faire en zig zag*/
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            vector->vector[i*8+j] = frequential_bloc_get_matrice(freq_bloc, i, j);
             // mauvaise implémentation
        }
    }
    return vector;
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
