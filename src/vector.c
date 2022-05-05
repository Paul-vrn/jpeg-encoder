#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "bloc.h"
#include "htables.h"


struct vector_t {
    struct vector_t *next;
    int16_t vector[64];
};

/**
 * @brief create a new vector from a bloc by zig zag
 * 
*/
struct vector_t* create_vector(struct bloc_t *bloc){
    struct vector_t* vector = calloc(1, sizeof(struct vector_t));
    vector->next = NULL;
    uint8_t **matrice = *bloc_get_matrice(bloc);
    // TODO: à changer pour faire en zig zag
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            vector->vector[i*8+j] = matrice[i][j];
        }
    }
    return vector;
}

// faire la quantification ici
void quantification(struct vector_t **vector){
    printf("vector %p\n", *vector);
}

//faire les DC et AC ici
void vector_dc_ac(struct vector_t **vector){
    codage_dc(vector);
    codage_ac(vector);
}
void codage_dc(struct vector_t **vector){
    struct vector_t *current = *vector;
    struct vector_t *prec = NULL;
    while (current != NULL){
        if (prec == NULL){
            //sans faire la différence
            current->vector[0] = 0;
        } else {
            //avec la différence
            current->vector[0] = current->vector[0] - prec->vector[0];
        }
        current = current->next;
    }
}
void codage_ac(struct vector_t **vector){

}
void vectors_destroy(struct vector_t **vector){
    struct vector_t *tmp = *vector;
    while (tmp != NULL){
        struct vector_t *tmp2 = tmp->next;
        free(tmp);
        tmp = tmp2;
    }
    *vector = NULL;
}

//get the number of bits needed to encode the number
uint32_t get_bits_needed(int16_t number){
    uint32_t bits_needed = 0;
    if (number < 0){
        number = -number;
        //bits_needed++;
    }
    while (number > 0){
        number = number >> 1;
        bits_needed++;
    }
    return bits_needed;
}