#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

/**
 * @brief 
 * 
 */
struct frequential_bloc_t {
    struct frequential_bloc_t *next;
    int16_t matrice[8][8];
};

/**
 * @brief 
 * 
 * @param frequential_bloc 
 * @param i 
 * @param j 
 * @return int16_t 
 */
int16_t frequential_bloc_get_matrice(struct frequential_bloc_t *frequential_bloc, uint8_t i, uint8_t j){
    return frequential_bloc->matrice[i][j];
}

/**
 * @brief 
 * 
 * @param frequential_blocs 
 */
void frequential_blocs_destroy(struct frequential_bloc_t *frequential_blocs){
    struct frequential_bloc_t *tmp = frequential_blocs;
    while (tmp != NULL){
        struct frequential_bloc_t *tmp2 = tmp->next;
        free(tmp);
        tmp = tmp2;
    }
}

//faire le DTC ici

