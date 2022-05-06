#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "bloc.h"
#include "frequential_bloc.h"

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
    struct frequential_bloc_t *bloc1 = dct(bloc);
    // struct bloc *bloco1 = bloc_create(bloc1);
    frequential_bloc_print(bloc1);
} 


int main(void)
{
    test_dct();
    return EXIT_SUCCESS;
}