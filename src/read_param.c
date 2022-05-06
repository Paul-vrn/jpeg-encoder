#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int H1 = 1;
int H2 = 1;
int H3 = 1;
int V1 = 1;
int V2 = 1;
int V3 = 1;
char *OUTFILE;
char *INFILE;

/**
 * @brief Lis les paramètre d'entré du programme et modifie des variables global 
 * qui seront utilisées dans les autres programmes
 * 
 * @param argc 
 * @param argv 
 */
void read_param(int argc, char *argv[]){

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

                OUTFILE = calloc(len - 9, sizeof(char));
                strncpy(OUTFILE, argv[i] + 10, len - 10);
                OUTFILE[len - 10] = '\0';


            } else if (strcmp(sample, "--sample=") == 0){

                char arg[len - 8];
                strncpy(arg, argv[i] + 9, len - 9);
                arg[len - 9] = '\0';
                H1 = arg[0] - '0';
                V1 = arg[2] - '0';
                H2 = arg[4] - '0';
                V2 = arg[6] - '0';
                H3 = arg[8] - '0';
                V3 = arg[10] - '0';

            } else if (strcmp(in, ".ppm") == 0 || strcmp(in, ".pgm") == 0){

                INFILE = calloc(len, sizeof(char));
                strcpy(INFILE, argv[i]);

            } else  {

                printf("Le paramètre suivant n'est pas bon : %s (utiliser --help pour plus d'informations)\n", argv[i]);

            }

            i++;


        }

        if (INFILE == NULL){

            printf("Le programme prend au moins en argument un fichier ppm/pgm a convertir\n");

        } else if (OUTFILE == NULL){

            int len = strlen(INFILE);
            OUTFILE = calloc(len, sizeof(char));
            strcpy(OUTFILE, INFILE);
            OUTFILE[len-1] = 'g';
            OUTFILE[len-2] = 'p';
            OUTFILE[len-3] = 'j';


        }


    }

}



int main(int argc, char *argv[]){


    read_param(argc, argv);
    printf("H1 = %i\n", H1);
    printf("V1 = %i\n", V1);
    printf("H2 = %i\n", H2);
    printf("V2 = %i\n", V2);
    printf("H3 = %i\n", H3);
    printf("V3 = %i\n", V3);
    printf("outfile = %s\ninfile = %s\n", OUTFILE, INFILE);


    return EXIT_SUCCESS;

}