#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief La fonction lis l'image demander et retourn un pointeur vers 3 tableau avec les composante RGB si ppm et vers un tableau Y et deux NULL pour pgm
 * 
 * @param argc 
 * @param argv 
 * @return uint8_t** 
 */
uint8_t ***creat_matrix(uint32_t *height, uint32_t *width, uint8_t *type, char **filename){

    int nb;
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

        if ((int)arg == 10){ // En ascii 10 correspond à un retour a la ligne

            i++;

        }
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

    





    uint8_t ***matrixs = calloc(3, sizeof(uint8_t));
    

    
    if (*type == 5){

        uint8_t *y_lines = calloc((*width)*(*height), sizeof(uint8_t));
        uint8_t **y_component = calloc(*height, sizeof(uint8_t));

        for (i = 0; i < *height; i++){

            y_component[i] = y_lines + i*(*width);


        }

        matrixs[0] = y_component;
        matrixs[1] = NULL;
        matrixs[2] = NULL;



        for (i = 0; i < *height; i++){
            for (j = 0; j < *width; j++){

                nb = fscanf(img, "%c", &r);
                matrixs[0][i][j] = r;

            }
        }

    } else if (*type == 6){

        uint8_t *r_lines = calloc((*width)*(*height), sizeof(uint8_t));
        uint8_t **r_component = calloc(*height, sizeof(uint8_t));
        uint8_t *g_lines = calloc((*width)*(*height), sizeof(uint8_t));
        uint8_t **g_component = calloc(*height, sizeof(uint8_t));
        uint8_t *b_lines = calloc((*width)*(*height), sizeof(uint8_t));
        uint8_t **b_component = calloc(*height, sizeof(uint8_t));

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

                nb = fscanf(img, "%c", &r);
                matrixs[0][i][j] = r;
                nb = fscanf(img, "%c", &g);
                matrixs[1][i][j] = g;
                nb = fscanf(img, "%c", &b);
                matrixs[2][i][j] = b;

            }
        }




    }
    return matrixs;






}


























