/**
 * @file read_pic.c
 * @author Axel Perrin (axel.perrin@grenoble-inp.org)
 * @brief file to read pixels of the ppm/pgm image
 * @version 1.0
 * @date 2022-05-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief Creat 3 matrixes from the input ppm pictures. If the picture is a ppm file the 3 matrixes are for R, G and B.
 * If the picture is a pgm file the first matrixe is for gray level and the others two are NULL.
 * 
 * @param height 
 * @param width 
 * @param type 
 * @param filename 
 * @return uint8_t*** 
 */
uint8_t ***creat_matrix(uint32_t *height, uint32_t *width, uint8_t *type, char **filename){


    uint8_t r;
    uint8_t g;
    uint8_t b;
    char arg;
    uint32_t i = 0;
    uint32_t j = 0;

    FILE *img = fopen(*filename, "r");
    
    while (i < 1){ 
        arg = fgetc(img);
        if ((int)arg == 53 || (int)arg == 54){
            *type = arg - '0';
        }

        i = ((int)arg==10) ? i+1 : i;// En ascii 10 correspond à un retour a la ligne
    }

    arg = fgetc(img);

    while((int)arg != 32){ // On lis la width de l'image
        *width = 10*(*width) + (arg - '0');
        arg = fgetc(img);
    }

    arg = fgetc(img);

    while((int)arg != 10){ // On lis la height de l'image
        *height = 10*(*height) + (arg - '0');
        arg = fgetc(img);
    }

    do{ // On passe le parametre d'echelle pour aller au données brute
        arg = fgetc(img);
    } while((int)arg != 10);

    uint8_t ***matrixs = calloc(3, sizeof(uint8_t **));
    
    if (*type == 5){

        uint8_t *y_lines = calloc((*width)*(*height), sizeof(uint8_t));
        uint8_t **y_component = calloc(*height, sizeof(uint8_t *));

        for (i = 0; i < *height; i++){

            y_component[i] = y_lines + i*(*width);


        }

        matrixs[0] = y_component;
        matrixs[1] = NULL;
        matrixs[2] = NULL;



        for (i = 0; i < *height; i++){
            for (j = 0; j < *width; j++){

                fscanf(img, "%c", &r);
                matrixs[0][i][j] = r;

            }
        }

    } else if (*type == 6){

        uint8_t *r_lines = calloc((*width)*(*height), sizeof(uint8_t));
        uint8_t **r_component = calloc(*height, sizeof(uint8_t *));
        uint8_t *g_lines = calloc((*width)*(*height), sizeof(uint8_t));
        uint8_t **g_component = calloc(*height, sizeof(uint8_t *));
        uint8_t *b_lines = calloc((*width)*(*height), sizeof(uint8_t));
        uint8_t **b_component = calloc(*height, sizeof(uint8_t *));

        for (i = 0; i < *height; i++){
            r_component[i] = r_lines + i*(*width);
            g_component[i] = g_lines + i*(*width);
            b_component[i] = b_lines + i*(*width);
        }

        matrixs[0] = r_component;
        matrixs[1] = g_component;
        matrixs[2] = b_component;

        for (i = 0; i < *height; i++){
            for (j = 0; j < *width; j++){
                fscanf(img, "%c", &r);
                matrixs[0][i][j] = r;
                fscanf(img, "%c", &g);
                matrixs[1][i][j] = g;
                fscanf(img, "%c", &b);
                matrixs[2][i][j] = b;
            }
        }

    }
    fclose(img);

    return matrixs;
}

/**
 * @brief Free the memory allocated for the matrixes.
 * 
 * @param matrix 
 */
void free_matrix(uint8_t ***matrix){
    if (matrix[1] == NULL){
        free(matrix[0][0]);
        free(matrix[0]);
    } else {
        for(int i = 0; i < 3; i++){
            free(matrix[i][0]);
            free(matrix[i]);
        }
    }
    free(matrix);
}


























