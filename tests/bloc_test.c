#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "bloc.h"

int G = 0;

int main(void)
{
    struct bloc_t *bloc1 = bloc_create(NULL);
    bloc_print(bloc1);
    G = 1;
    printf("%d\n", G);
    return EXIT_SUCCESS;
}
