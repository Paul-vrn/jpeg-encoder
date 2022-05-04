#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "bloc.h"

struct mcu_t {
    struct bloc_t *Y;
    struct bloc_t *Cb;
    struct bloc_t *Cr;
    struct mcu_t *next;
};

struct mcu_t *mcu_create(struct bloc_t *Y, struct bloc_t *Cb, struct bloc_t *Cr){
    struct mcu_t *mcu = calloc(1, sizeof(struct mcu_t));
    mcu->Y = Y;
    mcu->Cb = Cb;
    mcu->Cr = Cr;
    return mcu;
}

void mcu_destroy(struct mcu_t *mcu){
    blocs_destroy(mcu->Y);
    blocs_destroy(mcu->Cb);
    blocs_destroy(mcu->Cr);
    free(mcu);
}

void mcu_print(struct mcu_t *mcu){
    printf("MCU:\n");
    printf("Y:\n");
    bloc_print(mcu->Y);
    printf("Cb:\n");
    bloc_print(mcu->Cb);
    printf("Cr:\n");
    bloc_print(mcu->Cr);
}

void mcu_sous_echantillonne(struct mcu_t *mcu){
    blocs_fusion(&mcu->Cb);
    blocs_fusion(&mcu->Cr);
}
