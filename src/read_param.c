/**
 * @file read_param.c
 * @author Axel Perrin
 * @brief file to read the parameters of command line
 * @version 1.0
 * @date 2022-05-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * @brief Read the parameters from the command line and store them in the function parameters.
 *  These parameters need to be initialized before calling the function.
 * 
 * @param argc 
 * @param argv 
 * @param H1 
 * @param V1 
 * @param H2 
 * @param V2 
 * @param H3 
 * @param V3 
 * @param OUTFILE 
 * @param INFILE 
 */
void read_param(int argc, char *argv[], uint8_t *H1, uint8_t *V1, uint8_t *H2, uint8_t *V2, uint8_t *H3, uint8_t *V3, char **OUTFILE, char **INFILE){

    int i = 1;

    if (argc == 1){
        printf("ppm2jpg prend au moins le fichier à convertir en argument\n");
        printf("Pour plus d'information sur les paramètres, utiliser --help\n");
        exit(0);
    } else if (argc > 5){
        printf("ppm2jpg prend 4 arguments au maximum, utiliser --help pour en savoir plus\n");
        exit(0);
    }
    else{
        while (i < argc){
            int len = strlen(argv[i]);
            char out[11];
            strncpy(out, argv[i], 10);
            out[10] = '\0';

            char sample[10];
            strncpy(sample, argv[i], 9);
            sample[9] = '\0';

            char in[5];
            strncpy(in, argv[i] + len - 4, 4);
            in[4] = '\0';

            if (strcmp(argv[i], "--help") == 0){

                printf("ppm2jpeg permet de convertir une image au format ppm/pgm en une image jpeg\n");
                printf("Le programme prend minimum le chemin vers l'image ppm en entrée\n");
                printf("2 options suplementaire sont disponible :\n\n");
                printf("    1. --args=h1xv1,h2xv2,h3xv3 permet de définir les facteur de sous echantillonage (par défaut 1x1,1x1,1x1) avec :\n");
                printf("            - h1 et v1 pour Y\n");
                printf("            - h2 et v2 pour Cb\n");
                printf("            - h3 et v3 pour Cr\n\n");
                printf("    2. --outfile= permet de définir le nom du fichier ppm qui sera sinon nom_fichier_ppm.jpg\n");


            } else if (strcmp(out, "--outfile=") == 0){

                *OUTFILE = calloc(len - 9, sizeof(char));
                strncpy(*OUTFILE, argv[i] + 10, len - 10);
                (*OUTFILE)[len - 10] = '\0';
            } else if (strcmp(sample, "--sample=") == 0){
                char arg[len - 8];
                strncpy(arg, argv[i] + 9, len - 9);
                arg[len - 9] = '\0';
                *H1 = arg[0] - '0';
                *V1 = arg[2] - '0';
                *H2 = arg[4] - '0';
                *V2 = arg[6] - '0';
                *H3 = arg[8] - '0';
                *V3 = arg[10] - '0';

                if (*H1<1 || *H1>4 || *V1<1 || *V1>4 || *H2<1 || *H2>4 || *V2<1 || *V2>4 || *H3<1 || *H3>4 || *V3<1 || *V3>4){

                    printf("Les facteurs d'échantillonage doivent tous etre compris entre 1 et 4\n");

                }

                if ((*H1 * *V1) + (*H2 * *V2) + (*H3 * *V3) > 10){

                    printf("La somme de h1*v1, h2*v2 et h3*v3 ne doit pas exceder 10\n");

                }

                if (*H1%*H2 != 0 || *H1%*H3 != 0 || *V1%*V2 != 0 || *V1%*V3 != 0){

                    printf("Les facteurs d'échantillonnage des chrominances doivent diviser parfaitement ceux de la luminance\n");

                }

            } else if (strcmp(in, ".ppm") == 0 || strcmp(in, ".pgm") == 0){
                *INFILE = calloc(len+1, sizeof(char));
                strcpy(*INFILE, argv[i]);
            } else  {
                printf("Le paramètre suivant n'est pas bon : %s (utiliser --help pour plus d'informations)\n", argv[i]);
            }
            i++;
        }
        if (*INFILE == NULL){
            printf("Le programme prend au moins en argument un fichier ppm/pgm a convertir\n");
        } else if (*OUTFILE == NULL){
            int len = strlen(*INFILE);
            *OUTFILE = calloc(len+1, sizeof(char));
            strcpy(*OUTFILE, *INFILE);
            (*OUTFILE)[len-1] = 'g';
            (*OUTFILE)[len-2] = 'p';
            (*OUTFILE)[len-3] = 'j';
        }
    }
}



