#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "mcu.h"
#include "frequential_bloc.h"
#include "bloc.h"


void test_sous_echantillonne(void)
{
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
    struct bloc_t *bloc1 = bloc_create(matrice1);
    struct bloc_t *bloc2 = bloc_create(matrice2);
    bloc_set_next(bloc1, bloc2);
    struct mcu_t *mcu = mcu_create(NULL, bloc1, NULL, 8, 8);
    mcu_print(mcu);
    mcu_destroy(mcu);
    return;
}

void test_decoupage_mcu(){
    uint8_t p[12][20] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
        {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
        {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
        {7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
        {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8},
        {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
        {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
        {11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11},
    };
    
    uint8_t **pixels = (uint8_t **)malloc(sizeof(uint8_t *) * 12);
    for (uint32_t i = 0; i < 12; i++)
    {
        pixels[i] = (uint8_t *)malloc(sizeof(uint8_t) * 20);
        for (uint32_t j = 0; j < 20; j++)
        {
            pixels[i][j] = p[i][j];
        }
    }
    uint8_t **tab[3] = {pixels, pixels, pixels};
    //struct mcu_t* mcu = decoupage_mcu(tab, 12, 20, false, 4, 2, 0);
    //mcus_print(mcu);
}

void test_mcu_dct(void)
{
    uint8_t matrice1[8][8] = {
        {0x75, 0x75, 0x76, 0x77, 0x78, 0x7A, 0x7B, 0x7B},
        {0x75, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B},
        {0x75, 0x76, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7A},
        {0x76, 0x76, 0x77, 0x77, 0x78, 0x79, 0x7A, 0x7A},
        {0x76, 0x77, 0x77, 0x78, 0x78, 0x79, 0x79, 0x79},
        {0x77, 0x77, 0x77, 0x78, 0x78, 0x78, 0x79, 0x79},
        {0x77, 0x77, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78},
        {0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78, 0x78}};
    //struct bloc_t bloc = bloc_create(matrice1);
    struct mcu_t *mcu = mcu_create(NULL, bloc_create(matrice1), NULL, 8, 8);

    mcu_dct2(mcu);

    mcu_print(mcu);

}
// TODO : faire un test avec une matrice 16x24 et 4:2:2

int main(void)
{
    printf("test mcu!\n"); 
    //test_sous_echantillonne();
    //test_decoupage_mcu();
    test_mcu_dct();
    return EXIT_SUCCESS;
}

