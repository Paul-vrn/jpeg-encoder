#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint32_t HEIGHT = 0;
uint32_t WIDTH = 0;
int TYPE;

/**
 * @brief La fonction lis l'image demander et retourn un pointeur vers 3 tableau avec les composante RGB si ppm et vers un tableau Y et deux NULL pour pgm
 * 
 * @param argc 
 * @param argv 
 * @return uint8_t** 
 */
uint8_t ***creat_matrix(int argc, char *argv[]){


    int nb;
    uint8_t r;
    uint8_t g;
    uint8_t b;
    char arg;
    uint32_t i = 0;
    uint32_t j = 0;

    FILE *img = fopen(argv[1], "r");
    
    while (i < 1){ 

        arg = fgetc(img);
        printf("%c", arg);

        if ((int)arg == 53 || (int)arg == 54){

            TYPE = arg - '0';

        }

        if ((int)arg == 10){ // En ascii 10 correspond à un retour a la ligne

            i++;

        }
    }

    arg = fgetc(img);

    while((int)arg != 32){ // On lis la WIDTH de l'image

        WIDTH = 10*WIDTH + (arg - '0');
        arg = fgetc(img);

    }

    arg = fgetc(img);

    while((int)arg != 10){ // On lis la HEIGHT de l'image

        HEIGHT = 10*HEIGHT + (arg - '0');
        arg = fgetc(img);

    }

    do{ // On passe le parametre d'echelle pour aller au données brute

        arg = fgetc(img);


    } while((int)arg != 10);




    // uint8_t *r_lines = calloc(WIDTH*HEIGHT, sizeof(uint8_t));
    // uint8_t **r_component = calloc(HEIGHT, sizeof(uint8_t));
    // uint8_t *g_lines = calloc(WIDTH*HEIGHT, sizeof(uint8_t));
    // uint8_t **g_component = calloc(HEIGHT, sizeof(uint8_t));
    // uint8_t *b_lines = calloc(WIDTH*HEIGHT, sizeof(uint8_t));
    // uint8_t **b_component = calloc(HEIGHT, sizeof(uint8_t));
    uint8_t ***matrixs = calloc(3, sizeof(uint8_t));
    
    // for (i = 0; i < HEIGHT; i++){

    //     r_component[i] = r_lines + i*WIDTH;
    //     g_component[i] = g_lines + i*WIDTH;
    //     b_component[i] = b_lines + i*WIDTH;


    // }

    // matrixs[0] = r_component;
    // matrixs[1] = g_component;
    // matrixs[2] = b_component;

    
    if (TYPE == 5){

        uint8_t *y_lines = calloc(WIDTH*HEIGHT, sizeof(uint8_t));
        uint8_t **y_component = calloc(HEIGHT, sizeof(uint8_t));

        for (i = 0; i < HEIGHT; i++){

            y_component[i] = y_lines + i*WIDTH;


        }

        matrixs[0] = y_component;
        matrixs[1] = NULL;
        matrixs[2] = NULL;



        for (i = 0; i < HEIGHT; i++){
            for (j = 0; j < WIDTH; j++){

                nb = fscanf(img, "%c", &r);
                matrixs[0][i][j] = r;

            }
        }

    } else if (TYPE == 6){

        uint8_t *r_lines = calloc(WIDTH*HEIGHT, sizeof(uint8_t));
        uint8_t **r_component = calloc(HEIGHT, sizeof(uint8_t));
        uint8_t *g_lines = calloc(WIDTH*HEIGHT, sizeof(uint8_t));
        uint8_t **g_component = calloc(HEIGHT, sizeof(uint8_t));
        uint8_t *b_lines = calloc(WIDTH*HEIGHT, sizeof(uint8_t));
        uint8_t **b_component = calloc(HEIGHT, sizeof(uint8_t));

        for (i = 0; i < HEIGHT; i++){

            r_component[i] = r_lines + i*WIDTH;
            g_component[i] = g_lines + i*WIDTH;
            b_component[i] = b_lines + i*WIDTH;


        }

        matrixs[0] = r_component;
        matrixs[1] = g_component;
        matrixs[2] = b_component;

        for (i = 0; i < HEIGHT; i++){
            for (j = 0; j < WIDTH; j++){

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




int main(int argc, char *argv[]){

    uint8_t ***matrix = creat_matrix(argc, argv);


    printf("%u %u %i\n", HEIGHT, WIDTH, TYPE);


    return EXIT_SUCCESS;
}





















