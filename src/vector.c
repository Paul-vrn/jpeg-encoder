/**
 * @file vector.c
 * @author Paul Vernin (paul.vernin@grenoble-inp.org)
 * @brief file containing every functions related to the vector type and his usage in quantification and zig-zag.
 * @version 1.0
 * @date 2022-05-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "qtables.h"
#include "frequential_bloc.h"
#include <math.h>

/**
 * @brief structure to represent a vector
 * 
 */
struct vector_t {
    struct vector_t *next; /** pointer to the next vector in the chained list*/
    int16_t vector[64]; /** array of 64 int16_t to store frequential values*/
};


/**
 * @brief getter of the index value of the vector
 * 
 * @param vector the vector
 * @param index the index
 * @return int16_t the value of the index
 */
int16_t vector_get(struct vector_t *vector, uint32_t index)
{
    return vector->vector[index];
}

/**
 * @brief getter of the next vector
 * 
 * @param vector the vector
 * @return struct vector_t* 
 */
struct vector_t *vector_get_next(struct vector_t *vector)
{
    return vector->next;
}


/**
 * @brief Create a vector object from an array of 64 values
 * 
 * @param tab the tab of values
 * @return struct vector_t* 
 */
struct vector_t* create_vector(int16_t tab[64]){
    struct vector_t *vector = calloc(1, sizeof(struct vector_t));
    for (int i = 0; i < 64; i++){
        vector->vector[i] = tab[i];
    }
    vector->next = NULL;
    return vector;
}



/**
 * @brief insert vector in the list at the end
 * @test✔️
 * @param vector the vector
 * @param next the next vector
 */
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

/**
 * @brief print vector
 * 
 * @param vector the vector
 */
void vector_print(struct vector_t *vector){
    for (int i = 0; i < 64; i++){
        printf("%x ", vector->vector[i]);
        if (i % 8 == 7){
            printf("\n");
        }
    }
}
/**
 * @brief print vectors
 * 
 * @param vector the first vector of the list
 */
void vectors_print(struct vector_t *vectors){
    struct vector_t *tmp = vectors;
    while (tmp != NULL){
        vector_print(tmp);
        tmp = tmp->next;
    }
}

/**
 * @brief Create a vector from freq bloc by applying zigzag method
 * @test✔️
 * @param freq_bloc the frequential bloc
 * @return struct vector_t* the vector created
 */
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
 * @brief apply quantification to a vectors Y
 * @test✔️
 * @param vectors the first vector of the list
 */
void vectors_quantificationY(struct vector_t *vectors){
    struct vector_t *vector = vectors;
    while (vector != NULL){
        for (uint8_t i = 0; i < 64; i++){
            vector->vector[i] = (int16_t) round(vector->vector[i] / quantification_table_Y[i]);
        }
        vector = vector->next;
    }
}

/**
 * @brief apply the quantification table for vectors of Cr or Cb in the list
 * @test✔️
 * @param vectors the first vector of the list
 */
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
 * @brief destroy vectors list
 * @test✔️
 * @param head the first vector of the list
 */
void vectors_destroy(struct vector_t **head){
    struct vector_t *current = *head;
    while (current != NULL){
        struct vector_t *next = current->next;
        free(current);
        current = next;
    }
}
