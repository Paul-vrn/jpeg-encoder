#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "read_param.h"
#include "read_pic.h"


bool GRIS  = true;

int main(int argc, char *argv[])
{
    uint32_t HEIGHT = 0;
    uint32_t WIDTH = 0;
    int TYPE;

    int H1 = 1;
    int H2 = 1;
    int H3 = 1;
    int V1 = 1;
    int V2 = 1;
    int V3 = 1;
    char *OUTFILE;
    char *INFILE;

    read_param(argc, argv, &H1, &V1, &H2, &V2, &H3, &V3, &OUTFILE, &INFILE);

    uint8_t ***matr = creat_matrix(&HEIGHT, &WIDTH, &TYPE, &INFILE);

    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){

            printf("%u ", matr[0][i][j]);
        }
        printf("\n");


    }
    printf("type = %i\n", TYPE);
    printf("hauteur = %u // largeur = %u\n", HEIGHT, WIDTH);
    printf("outfile = %s\n", OUTFILE);
    printf("infile = %s\n", INFILE);
    printf("h1 = %i, v1 = %i\n", H1, V1);
    printf("h2 = %i, v2 = %i\n", H2, V2);
    printf("h3 = %i, v3 = %i\n", H3, V3);


    return EXIT_SUCCESS;
}
