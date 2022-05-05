#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint32_t hauteur = 0;
uint32_t largeur = 0;
int type;


uint8_t **creat_matrix(int argc, char *argv[]){


    int nb;
    uint8_t a;
    char arg;
    int i = 0;
    int j = 0;

    FILE *img = fopen(argv[1], "r");
    
    while (i < 1){ 

        arg = fgetc(img);
        printf("%c", arg);

        if ((int)arg == 10){ // En ascii 10 correspond à un retour a la ligne

            i++;

        }
    }

    arg = fgetc(img);

    while((int)arg != 32){ // On lis la largeur de l'image

        largeur = 10*largeur + (arg - '0');
        arg = fgetc(img);

    }

    arg = fgetc(img);

    while((int)arg != 10){ // On lis la hauteur de l'image

        hauteur = 10*hauteur + (arg - '0');
        arg = fgetc(img);

    }

    do{ // On passe le parametre d'echelle pour aller au données brute

        arg = fgetc(img);


    } while((int)arg != 10);




    uint8_t *lignes = calloc(largeur*hauteur, sizeof(uint8_t));
    uint8_t **matrice = calloc(hauteur, sizeof(uint8_t));
    for (i = 0; i < hauteur; i++){

        matrice[i] = lignes + i*largeur;

    }



    for (i = 0; i < hauteur; i++){
        for (j = 0; j < largeur; j++){

            nb = fscanf(img, "%c", &a);
            matrice[i][j] = a;

        }
    }

    
    return matrice;






}




void main(int argc, char *argv[]){

    uint8_t **matrix = creat_matrix(argc, argv);

    for (int i = 0; i < hauteur; i++){
        for (int j = 0; j < largeur; j++){

            printf("%u ", matrix[i][j]);

        }
        printf("\n");
    }

    printf("%u %u\n", hauteur, largeur);


}



















