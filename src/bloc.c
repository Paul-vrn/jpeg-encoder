#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include <math.h>

struct bloc_t {
    struct bloc_t *next;
    uint8_t matrice[8][8];
};

void bloc_set_next(struct bloc_t *bloc, struct bloc_t *next)
{
    bloc->next = next;
}
void bloc_set_matrice(struct bloc_t *bloc, uint8_t matrice[8][8]){
    for (uint32_t i = 0; i < 8; i++){
        for (uint32_t j = 0; j < 8; j++){
            bloc->matrice[i][j] = matrice[i][j];
        }
    }
}

struct bloc_t *bloc_get_next(struct bloc_t *bloc){
    return bloc->next;
}
uint8_t ***bloc_get_matrice(struct bloc_t *bloc){
    return NULL;
//    return &bloc->matrice;
}

void bloc_add(struct bloc_t **bloc, struct bloc_t *next){
    struct bloc_t *tmp = *bloc;
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
 * @brief Create a bloc
 * @test✔️
 * @param matrice The matrice of the bloc
 * @return struct bloc_t* The bloc
 */
struct bloc_t *bloc_create(uint8_t matrice[8][8]){
    struct bloc_t *bloc = calloc(1, sizeof(struct bloc_t));
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

/**
 * @brief function to create a bloc from a set of pixels
 * @test✔️
 * @param pixels matrix containing ALL the pixels
 * @param start_x x coordinate of the first pixel
 * @param end_x x coordinate of the last pixel
 * @param start_y y coordinate of the first pixel
 * @param end_y y coordinate of the last pixel
 * @return struct bloc_t* pointer to the new bloc
 */
struct bloc_t* bloc_create_from_pixels(uint8_t **pixels, uint32_t start_x, uint32_t end_x, uint32_t start_y, uint32_t end_y){
    //printf("start_x: %d, end_x: %d, start_y: %d, end_y: %d\n", start_x, end_x, start_y, end_y);
    struct bloc_t *bloc = calloc(1, sizeof(struct bloc_t));
    bloc->next = NULL;
    uint32_t k = 0;
    uint32_t l = 0;
    for (uint32_t i = start_y; i < end_y; i++){
        for (uint32_t j = start_x; j < end_x; j++){
            bloc->matrice[k][l] = pixels[i][j];
            l++;
        }
        k++;
        l = 0;
    }
    if (end_x-start_x==8 && end_y-start_y==8){
        return bloc;
    }
    k = 0;
    l = end_x - start_x;
    for (uint32_t i = start_y; i < end_y; i++){ 
        for (uint32_t j = end_x; j < start_x + 8; j++){ // de start+4 à start+8
            bloc->matrice[k][l] = pixels[i][end_x-1];
            l++;
        }
        k++;
        l = end_x - start_x;
    }

    k = end_y - start_y;
    l = 0;
    for (uint32_t i = end_y; i < start_y + 8; i++){
        for (uint32_t j = start_x; j < start_x+8; j++){
            if (j < end_x){
                bloc->matrice[k][l] = pixels[end_y-1][j];
            } else {
                bloc->matrice[k][l] = pixels[end_y-1][end_x-1];
            }
            l++;
        }
        k++;
        l = 0;
    }
    return bloc;
}

/**
 * @brief Destroy a bloc
 * @test✔️
 * @param bloc 
 */
void bloc_destroy(struct bloc_t *bloc) {
    free(bloc);
}

/**
 * @brief Destroy blocs
 * @test✔️
 * @param blocs 
 */
void blocs_destroy(struct bloc_t *blocs){
    struct bloc_t *bloc = blocs;
    while (bloc != NULL) {
        struct bloc_t *tmp = bloc;
        bloc = bloc->next;
        bloc_destroy(tmp);
    }
}

/**
 * @brief Print values of a bloc
 * @test✔️
 * @param bloc 
 */
void bloc_print(struct bloc_t *bloc){
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%u ", bloc->matrice[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief Print values of blocs
 * @test✔️
 * @param blocs
 */
void blocs_print(struct bloc_t *blocs){
    struct bloc_t *bloc = blocs;
    while (bloc != NULL) {
        bloc_print(bloc);
        bloc = bloc->next;
        printf("\n");
    }
}

/**
 * @brief function that merge 2 blocs line by line
 * @test✔️
 * @param bloc1 first block
 * @param bloc2 second block (to the right)
 * @return struct bloc_t* merged bloc
 */
struct bloc_t* fusion_2_blocs(struct bloc_t *bloc1, struct bloc_t *bloc2){
    struct bloc_t *bloc_fusion = bloc_create(NULL);
    for (uint32_t i = 0; i < 8; i++) {
        uint8_t k = 0;
        for (uint32_t j = 0; j < 8; j++) {
            if (k < 8) {
                bloc_fusion->matrice[i][j] = (uint8_t)(bloc1->matrice[i][k]+bloc1->matrice[i][k+1])/2;
            } else {
                bloc_fusion->matrice[i][j] = (uint8_t)(bloc2->matrice[i][k-8]+bloc2->matrice[i][k-7])/2;
            }
            k += 2;
        }
    }
    return bloc_fusion;
}

/**
 * @brief function that merge 4 blocs 2 lines by 2 lines, 
 * example : [0][0] = mean([0][0], [0][1], [1][0], [1][1])
 * @test❌
 * @param bloc1 first block
 * @param bloc2 second block (to the right)
 * @param bloc3 third block (bellow)
 * @param bloc4 fourth block (to the right and bellow)
 * @return struct bloc_t* merged bloc
 */
struct bloc_t* fusion_4_blocs(struct bloc_t *bloc1, struct bloc_t *bloc2, struct bloc_t *bloc3, struct bloc_t *bloc4){
    struct bloc_t *bloc_fusion = bloc_create(NULL);

    for (uint32_t i = 0; i < 8; i++) {
        uint8_t k = 0;
        for (uint32_t j = 0; j < 8; j++) {
            if (j*2 < 8){
                if (k < 8) {
                    bloc_fusion->matrice[i][j] = (uint8_t)(bloc1->matrice[i*2][k]+bloc1->matrice[i*2][k+1]+bloc1->matrice[(i+1)*2][k]+bloc1->matrice[(i+1)*2][k+1])/4;
                } else {
                    bloc_fusion->matrice[i][j] = (uint8_t)(bloc2->matrice[i*2][k]+bloc2->matrice[i*2][k+1]+bloc2->matrice[(i+1)*2][k]+bloc2->matrice[(i+1)*2][k+1])/4;
                }
            } else {
                if (k < 8) {
                    bloc_fusion->matrice[i][j] = (uint8_t)(bloc3->matrice[i*2][k]+bloc3->matrice[i*2][k+1]+bloc3->matrice[(i+1)*2][k]+bloc3->matrice[(i+1)*2][k+1])/4;
                } else {
                    bloc_fusion->matrice[i][j] = (uint8_t)(bloc4->matrice[i*2][k]+bloc4->matrice[i*2][k+1]+bloc4->matrice[(i+1)*2][k]+bloc4->matrice[(i+1)*2][k+1])/4;
                }
            }
            k += 2;
        }
    }
    return bloc_fusion;
}

/**
 * @brief function that merge blocs,
 * @test❌
 * @param blocs 
 */
void blocs_fusion(struct bloc_t **blocs){
    uint8_t count = 0;
    struct bloc_t *bloc = *blocs;
    //TODO : à changer quand il y a les variables globales qui permettent de dire si on fait une fusion par 2 ou 4
    while (bloc != NULL) {
        count++;
        bloc = bloc->next;
    }
    if (count == 1) {
        return;
    } else if (count == 2){
        struct bloc_t* bloc_fusion = fusion_2_blocs(bloc, bloc->next);
        blocs_destroy(bloc);
        bloc = bloc_fusion;        
    } else if (count == 4){
        struct bloc_t* bloc_fusion = (struct bloc_t*) fusion_4_blocs(bloc, bloc->next, bloc->next->next, bloc->next->next->next);
        blocs_destroy(bloc);
        bloc = bloc_fusion;        
    } else {
        //error
    } 
}
/**
 * @brief compare two blocs 
 * @test✔️
 * @param bloc1 
 * @param bloc2 
 * @return true if blocs are equal, false otherwise
 */
bool compare_blocs(struct bloc_t *bloc1, struct bloc_t *bloc2){
    for (uint32_t i = 0; i < 8; i++) {
        for (uint32_t j = 0; j < 8; j++) {
            if (bloc1->matrice[i][j] != bloc2->matrice[i][j]){
                return false;
            }
        }
    } 
    return true;
}