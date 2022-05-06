#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "bloc.h"

void test_fusion_2(){
    uint8_t matrice1[8][8] = {
        {117,117,117,117,118,118,119,120},
        {117,117,117,117,118,118,119,119},
        {117,117,118,118,118,118,119,119},
        {118,118,118,118,119,119,119,119},
        {118,118,119,119,119,119,120,120},
        {119,120,120,119,119,119,120,120},
        {119,119,119,120,120,120,120,120},
        {120,120,120,120,120,120,120,120}
    };

    uint8_t matrice2[8][8] = {
        {120,121,122,122,123,123,123,123},
        {120,121,121,122,122,122,123,123},
        {120,120,121,121,122,122,122,122},
        {120,120,121,121,122,122,122,122},
        {120,120,121,121,121,121,121,121},
        {120,120,120,120,121,121,121,121},
        {120,120,120,120,120,120,120,120},
        {120,120,120,120,120,120,120,120},
    };

    uint8_t matrice_result[8][8] = {
        {117,117,118,119,120,122,123,123},
        {117,117,118,119,120,121,122,123},
        {117,118,118,119,120,121,122,122},
        {118,118,119,119,120,121,122,122},
        {118,119,119,120,120,121,121,121},
        {119,119,119,120,120,120,121,121},
        {119,119,120,120,120,120,120,120},
        {120,120,120,120,120,120,120,120},
    };
    struct bloc_t *bloc1 = bloc_create(matrice1);
    struct bloc_t *bloc2 = bloc_create(matrice2);
    struct bloc_t *bloc_result = bloc_create(matrice_result);
    struct bloc_t *bloc_fusion = fusion_2_blocs(bloc1, bloc2);
    assert(compare_blocs(bloc_fusion, bloc_result));
    bloc_destroy(bloc1);
    bloc_destroy(bloc2);
    bloc_destroy(bloc_fusion);
    bloc_destroy(bloc_result);
    return;
}

void test_dct(){
    uint8_t bloc[8][8] = {{139, 144, 149, 153, 155, 155, 155, 155},
                    {144, 151, 153, 156, 159, 156, 156, 156},
                    {150, 155, 160, 163, 158, 156, 156, 156},
                    {159, 161, 162, 160, 160, 159, 159, 159},
                    {159, 160, 161, 162, 162, 155, 155, 155},
                    {161, 161, 161, 161, 160, 157, 157, 157},
                    {162, 162, 161, 163, 162, 157, 157, 157},
                    {162, 162, 161, 161, 163, 158, 158, 158}};
    // for(uint8_t i=0; i<8; i++){
    //     for(uint8_t j=0; j<8; j++){
    //         printf("%f", coef_dct(bloc, i,j));
    //     }
    // }
    struct bloc_t *bloco = bloc_create(bloc);
    bloc_print(bloco);
    printf("\n");
    struct int_bloc_t *bloc1 = dct(bloc);
    // struct bloc *bloco1 = bloc_create(bloc1);
    int_bloc_print(bloc1);
} 

int main(void)
{
    //test_fusion_2();
    //test_dct();
    return EXIT_SUCCESS;
}