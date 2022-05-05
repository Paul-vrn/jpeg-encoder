#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

struct bloc_t {
    struct bloc_t *next;
    uint8_t matrice[8][8];
};

void bloc_set_next(struct bloc_t *bloc, struct bloc_t *next)
{
    bloc->next = next;
}
void bloc_set_matrice(struct bloc_t *bloc, uint8_t matrice[8][8]){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            bloc->matrice[i][j] = matrice[i][j];
        }
    }
}

struct bloc_t *get_next(struct bloc_t *bloc){
    return bloc->next;
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
 * @test❌
 * @param pixels matrix containing ALL the pixels
 * @param start_x x coordinate of the first pixel
 * @param end_x x coordinate of the last pixel
 * @param start_y y coordinate of the first pixel
 * @param end_y y coordinate of the last pixel
 * @return struct bloc_t* pointer to the new bloc
 */
struct bloc_t* bloc_create_from_pixels(uint8_t **pixels, uint32_t start_x, uint32_t end_x, uint32_t start_y, uint32_t end_y){
    struct bloc_t *bloc = calloc(1, sizeof(struct bloc_t));
    bloc->next = NULL;
    for (uint32_t i = start_x; i < end_x; i++){
        for (uint32_t j = start_y; j < end_y; j++){
            bloc->matrice[i][j] = pixels[i][j];
        }
        for (uint32_t j = end_y; j < 8; j++){
            bloc->matrice[i][j] = pixels[i][end_y];
        }
    }
    for (uint32_t i = end_x; i < 8; i++){
        for (uint32_t j = start_y; j < end_y; j++){
            bloc->matrice[i][j] = pixels[end_x][j];
        }
        for (uint32_t j = end_y; j < 8; j++){
            bloc->matrice[i][j] = pixels[end_x][end_y];
        }
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
            printf("%d ", bloc->matrice[i][j]);
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
                //printf("[%i][%i] = %u = %u + %u\n",i,j, bloc_fusion->matrice[i][j],bloc1->matrice[i][k], bloc1->matrice[i][k+1]);
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

void blocs_fusion(struct bloc_t **blocs){
    uint8_t count = 0;
    struct bloc_t *bloc = *blocs;
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


uint32_t DCT(uint8_t**bloc, uint32_t i, uint32_t j){
    float pi = 3.14159265358;/*9793238462643383279502884197169399375105820;*/
    float n = 8;
    float resultat = 0;
    for(uint32_t x = 0; x < 8; x++){
        for(uint32_t y = 0; y < 8 ; y++){
            resultat += bloc[x][y] * cos(((2*x+1)*(float)i*pi)/(2*n)) * cos(((2*y+1)*(float)i*pi)/(2*n)); 
        }
    }
    if(i==0 && j==0){
        resultat *= (2/n) * 1/sqrt(2) * 1/sqrt(2); 
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

void DCT2(uint8_t**bloc){
    for(uint32_t i=0; i<8; i++){
        for(uint32_t j=0; j<8; j++){
            bloc[i][j] = bloc[i][j] - 128 ;
        }}
    for(uint32_t i=0; i<8; i++){
        for(uint32_t j=0; j<8; j++){
            bloc[i][j] = DCT(**bloc, i, j);
        }
    }
}

/* Il y a deja un main
void main(){
    uint8_t ligne1[] = {139, 144, 149, 153, 155, 155, 155, 155};
    uint8_t ligne2[] = {144, 151, 153, 156, 159, 156, 156, 156};
    uint8_t ligne3[] = {150, 155, 150, 153, 158, 156, 156, 156};
    uint8_t ligne4[] = {159, 161, 162, 160, 160, 159, 159, 159};
    uint8_t ligne5[] = {159, 160, 161, 162, 162, 155, 155, 155};
    uint8_t ligne6[] = {161, 161, 161, 161, 160, 157, 157, 157};
    uint8_t ligne7[] = {162, 162, 161, 163, 162, 157, 157, 157};
    uint8_t ligne8[] = {162, 162, 161, 161, 163, 158, 158, 158};
    uint8_t bloc[] = {ligne1, ligne2, ligne3, ligne4, ligne5, ligne6, ligne7, ligne8};
    bloc_print(bloc);
    DCT2(bloc);
    bloc_print(bloc);
} */

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
