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


int main(void)
{
    struct bloc_t *bloc1 = bloc_create(NULL);
    bloc_print(bloc1);
    bloc_destroy(bloc1);
    test_fusion_2();
    return EXIT_SUCCESS;
}