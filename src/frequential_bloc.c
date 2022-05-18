/**
 * @file frequential_bloc.c
 * @author Paul Vernin (paul.vernin@grenoble-inp.org) and Marc Félix-Henry (marc.felix-henry@grenoble-inp.org)
 * @brief file containing every functions related to the frequential bloc type and his usage in DCT.
 * @version 1.0
 * @date 2022-05-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <bloc.h>
#include <costable.h>

/**
 * @brief structure to represent a bloc containing frequential values
 * 
 */
struct frequential_bloc_t {
    struct frequential_bloc_t *next; /** pointer to the next frequential bloc*/
    int16_t matrice[8][8]; /** matrix 8x8 containing the frequential value after the DCT*/
};

/**
 * @brief setter of the next freq bloc
 * 
 * @param frequential_bloc the frequential bloc
 * @param next pointer to the next freq bloc
 */
void frequential_bloc_set_next(struct frequential_bloc_t *frequential_bloc, struct frequential_bloc_t *next)
{
    frequential_bloc->next = next;
}

/**
 * @brief getter of the next freq bloc
 * 
 * @param bloc 
 * @return struct frequential_bloc_t* 
 */
struct frequential_bloc_t* frequential_bloc_get_next(struct frequential_bloc_t *bloc)
{
    return bloc->next;
}

int16_t frequential_bloc_get_matrice(struct frequential_bloc_t *frequential_bloc, uint8_t i, uint8_t j){
    return frequential_bloc->matrice[i][j];
}


/**
 * @brief insert bloc in the list at the end
 * 
 * @param bloc 
 * @param next 
 */
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

/**
 * @brief destroy a list of freq bloc
 * 
 * @param frequential_blocs 
 */
void frequential_blocs_destroy(struct frequential_bloc_t **head){
    struct frequential_bloc_t *current = *head;
    while (current != NULL)
    {
        struct frequential_bloc_t *next = current->next;
        free(current);
        current = next;
    }
}

/**
 * @brief create a frequentiel bloc from a matrice or NULL
 * @test✔️
 * @param matrice 
 * @return struct frequential_bloc_t* 
 */
struct frequential_bloc_t *frequential_bloc_create(int16_t matrice[8][8]){
    struct frequential_bloc_t *bloc = calloc(1, sizeof(struct frequential_bloc_t));
    bloc->next = NULL;
    if (matrice != NULL){
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
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

/**
 * @brief print a frequential bloc
 * 
 * @param bloc 
 */
void frequential_bloc_print(struct frequential_bloc_t *bloc){
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%x ", bloc->matrice[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief print a list of frequential bloc
 * 
 * @param frequential_blocs 
 */
void frequential_blocs_print(struct frequential_bloc_t *frequential_blocs){
    struct frequential_bloc_t *tmp = frequential_blocs;
    while (tmp != NULL){
        frequential_bloc_print(tmp);
        tmp = tmp->next;
    }
}

/**
 * @brief calculate the coeficient for every value of the bloc
 * @test✔️
 * @param bloc_copy 
 * @param i 
 * @param j 
 * @return float 
 */
float coef_dct(int16_t bloc_copy[8][8], uint32_t i, uint32_t j){

    float n = 8;
    float resultat = 0.0;
    for(uint32_t x = 0; x < 8; x++){
        for(uint32_t y = 0; y < 8 ; y++){
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

/**
 * @brief apply the DCT on a bloc and return the result as a frequential bloc
 * @test✔️
 * @param bloc 
 * @return struct frequential_bloc_t* 
 */
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
            new_bloc[i][j] = (int16_t)coef_dct(bloc_copy, i, j);
        }
    }
    struct frequential_bloc_t *blocc = frequential_bloc_create(new_bloc);
    return blocc;
}

