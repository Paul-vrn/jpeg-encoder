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



void vector_add(struct vector_t **vector, struct vector_t *next){
    struct vector_t *tmp = *vector;
    if (tmp == NULL){
        *vector = next;
    } else {
        while (tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = next;
    }
}

void vector_print(struct vector_t *vector){
    for (int i = 0; i < 64; i++){
        printf("%x ", vector->vector[i]);
        if (i % 8 == 7){
            printf("\n");
        }
    }
}
void vectors_print(struct vector_t *vectors){
    struct vector_t *tmp = vectors;
    while (tmp != NULL){
        vector_print(tmp);
        tmp = tmp->next;
    }
}

/**
 * @brief Create a vector from bloc object
 * @test❌
 * @param freq_bloc 
 * @return struct vector_t* 
 */
struct vector_t* create_vector_from_bloc(struct frequential_bloc_t *freq_bloc){
    struct vector_t* vector = calloc(1, sizeof(struct vector_t));
    vector->next = NULL;
    /* TODO: à changer pour faire en zig zag*/
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (i+j % 2 == 0 && i+j < 8){
                vector->vector[i+(i+j+1)*(i+j)/2] = frequential_bloc_get_matrice(freq_bloc, i, j);
            } else if (i+j % 2 == 1 && i+j < 8){
            vector->vector[j+(i+j+1)*(i+j)/2] = frequential_bloc_get_matrice(freq_bloc, i, j);
            }
            else if(i+j % 2 == 0 && i+j >= 8){
                uint8_t iprime = 7-i;
                uint8_t jprime = 7-j;
                vector->vector[63-(iprime+(iprime+jprime+1)*(iprime+jprime)/2)] = frequential_bloc_get_matrice(freq_bloc, i, j);
            } else if (i+j % 2 == 1 && i+j >= 8){
                uint8_t iprime = 7-i;
                uint8_t jprime = 7-j;
                vector->vector[63-(jprime+(iprime+jprime+1)*(iprime+jprime)/2)] = frequential_bloc_get_matrice(freq_bloc, i, j);
            }
        }
    }
    return vector;
}


// Fonction emprunté à Arthur Lebeurier en attendant que la notre fonctionne
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

struct vector_t* create_vector_from_bloc2(struct frequential_bloc_t *freq_bloc){
 	int cpt = 0;
 	int len = 8;
    struct vector_t* vector = calloc(1, sizeof(struct vector_t));

 	for (int k = 0; k<2*len-1; k++){
 		if (k%2 == 0){
     		for (int j = max(0, k-len+1); j<=min(k,len-1); j++){
                vector->vector[cpt] = (int16_t) frequential_bloc_get_matrice(freq_bloc, k-j, j);
		    	cpt++;
 		    }
 	    } else {
     		for (int j = max(0, k-len+1); j<=min(k,len-1); j++){
                vector->vector[cpt] = (int16_t) frequential_bloc_get_matrice(freq_bloc, j, k-j);
 			    cpt++;
 		    }
 	    }
    }
    return vector;
}



void vectors_quantificationY(struct vector_t *vectors){
    struct vector_t *vector = vectors;
    while (vector != NULL){
        for (uint8_t i = 0; i < 64; i++){
            vector->vector[i] = (int16_t) round(vector->vector[i] / quantification_table_Y[i]);
        }
        vector = vector->next;
    }
}

void vectors_quantificationCbCr(struct vector_t *vectors){
    struct vector_t *vector = vectors;
    while (vector != NULL){
        for (uint8_t i = 0; i < 64; i++){
            vector->vector[i] = (int16_t) (vector->vector[i] / quantification_table_CbCr[i]);
        }
        vector = vector->next;
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
