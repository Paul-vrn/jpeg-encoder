#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "convert_RGB_to_YCbCr.h"

void test_convert_RGB_to_YCbCr(){
    
    uint8_t r[2][2] ={
        {0xb8, 0xb1},
        {0xb2, 0xb4}
    };
    uint8_t g[2][2] ={
        {0xa0, 0x9b},
        {0x9b, 0x9e}
    };
    uint8_t b[2][2] ={
        {0x92, 0x8d},
        {0x8d, 0x90}
    };
    uint8_t y[2][2]  ={{0xa6, 0xa0},{0xa0, 0xa3}};
    uint8_t cb[2][2] ={{0x75, 0x75},{0x75, 0x75}};
    uint8_t cr[2][2] ={{0x8d, 0x8c},{0x8d, 0x8c}};

    uint8_t rgb[3][2][2] ={
        {
            {0xb8, 0xb1},
            {0xb2, 0xb4}
        }, 
            {
            {0xa0, 0x9b},
            {0x9b, 0x9e}
        }, 
        {
            {0x92, 0x8d},
            {0x8d, 0x90}
        }
    };

    uint8_t ***matrice = calloc(3, sizeof(uint8_t **));
    for (int i = 0; i < 3; i++){
        matrice[i] = calloc(2, sizeof(uint8_t *));
        for (int j = 0; j < 2; j++){
            matrice[i][j] = calloc(2, sizeof(uint8_t));
            for (int k = 0; k < 2; k++){
                matrice[i][j][k] = rgb[i][j][k];
            }
        }
    }
    convert_RGB_to_YCbCr(matrice, 2, 2);
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 2; j++){
            for (int k = 0; k < 2; k++){
                printf("%x ", matrice[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}


int main(void)
{
    printf("test convert_RGB_to_YCbCr!\n"); 
    test_convert_RGB_to_YCbCr();
    return EXIT_SUCCESS;
}
