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

        

    //zig zag : créer le "zigzag" en fonction de l:h:v et du nombre de MCU (mcu_count)
    
    return EXIT_SUCCESS;
}
