#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

struct bloc_t {
    struct bloc_t *next;
    uint8_t matrice[8][8];
};


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

void bloc_destroy(struct bloc_t *bloc) {
    free(bloc);
}
void blocs_destroy(struct bloc_t *blocs){
    struct bloc_t *bloc = blocs;
    while (bloc != NULL) {
        struct bloc_t *tmp = bloc;
        bloc = bloc->next;
        bloc_destroy(tmp);
    }
}

void bloc_print(struct bloc_t *bloc){
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%d ", bloc->matrice[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief function that merge 2 blocs line by line
 * 
 * @param bloc1 
 * @param bloc2 
 * @return struct bloc_t* 
 */
struct bloc_t* fusion_2_blocs(struct bloc_t *bloc1, struct bloc_t *bloc2){
    struct bloc_t *bloc_fusion = bloc_create(NULL);
    for (int i = 0; i < 8; i++) {
        uint8_t j = 0;
        uint8_t k = 0;
        for (j = 0; j < 8; j++) {
            if (k <= 8) {
                bloc_fusion->matrice[i][j] = (bloc1->matrice[i][k]+bloc1->matrice[i][k+1])/2;
            } else {
                bloc_fusion->matrice[i][j] = (bloc2->matrice[i][k-8]+bloc2->matrice[i][k-7])/2;
            }
            k += 2;
        }
    }
    return bloc_fusion;
}

struct bloc_t* fusion_4_blocs(struct bloc_t *bloc1, struct bloc_t *bloc2, struct bloc_t *bloc3, struct bloc_t *bloc4){
    struct bloc_t *bloc_fusion = bloc_create(NULL);

    for (int i = 0; i < 8; i++) {
        uint8_t j = 0;
        uint8_t k = 0;
        for (j = 0; j < 8; j++) {
            if (j*2 <= 8){
                if (k <= 8) {
                    bloc_fusion->matrice[i][j] = (bloc1->matrice[i*2][k]+bloc1->matrice[i*2][k+1]+bloc1->matrice[(i+1)*2][k]+bloc1->matrice[(i+1)*2][k+1])/4;
                } else {
                    bloc_fusion->matrice[i][j] = (bloc2->matrice[i*2][k]+bloc2->matrice[i*2][k+1]+bloc2->matrice[(i+1)*2][k]+bloc2->matrice[(i+1)*2][k+1])/4;
                }
            } else {
                if (k <= 8) {
                    bloc_fusion->matrice[i][j] = (bloc3->matrice[i*2][k]+bloc3->matrice[i*2][k+1]+bloc3->matrice[(i+1)*2][k]+bloc3->matrice[(i+1)*2][k+1])/4;
                } else {
                    bloc_fusion->matrice[i][j] = (bloc4->matrice[i*2][k]+bloc4->matrice[i*2][k+1]+bloc4->matrice[(i+1)*2][k]+bloc4->matrice[(i+1)*2][k+1])/4;
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
    float pi = 3.141592653589793238462643383279502884197169399375105820;
    float n = 8;
    float resultat = 0;
    for(uint32_t x = 0; x < 8; x++){
        for(uint32_t y = 0; y < 8 ; y++){
            resultat += bloc[x][y] * cos(((2*x+1)*i*pi)/(2*n)) * cos(((2*y+1)*i*pi)/(2*n)); 
        }
    }
    if(i==0 && j==0){
        resultat *= (2/n) * 1/srqt(2) * 1/srqt(2); 
    }
    else if(i==0){
        resultat *= (2/n) * 1/srqt(2);
    }
    else if(j==0){
        resultat *= (2/n) * 1/srqt(2); 
    }
    else{
        resultat *= (2/n);
    }
    return resultat;
}

void DCT2(uint8_t**bloc){
    for(uint32_t i=0; i<8; i++){
        for(uint32_t j=0; j<8; j++){
            bloc[i][j] = DCT(**bloc, i, j);
        }

    }
}
