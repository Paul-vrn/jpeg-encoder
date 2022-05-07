#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * @brief Lis les paramètre d'entré du programme et modifie des variables global 
 * qui seront utilisées dans les autres programmes
 * 
 * @param argc 
 * @param argv 
 */
void read_param(int argc, char *argv[], uint8_t *H1, uint8_t *V1, uint8_t *H2, uint8_t *V2, uint8_t *H3, uint8_t *V3, char **OUTFILE, char **INFILE){

    int i = 1;

    if (argc == 1){

        printf("ppm2jpg prend au moins le fichier à convertir en argument\n");
        printf("Pour plus d'information sur les paramètres, utiliser --help\n");

    } else if (argc > 5){

        printf("ppm2jpg prend 4 arguments au maximum, utiliser --help pour en savoir plus\n");

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

                printf("help\n");

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

            } else if (strcmp(in, ".ppm") == 0 || strcmp(in, ".pgm") == 0){

                *INFILE = calloc(len, sizeof(char));
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
            *OUTFILE = calloc(len, sizeof(char));
            strcpy(*OUTFILE, *INFILE);
            (*OUTFILE)[len-1] = 'g';
            (*OUTFILE)[len-2] = 'p';
            (*OUTFILE)[len-3] = 'j';


        }


    }

}



