#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "bloc.h"
#include <stdbool.h>

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
    mcu->next = NULL;
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

struct mcu_t* decoupage_mcu(uint8_t **pixels, uint32_t height, uint32_t width, bool gris){
    struct mcu_t *mcu_current = NULL;
    if (gris){
        uint32_t start_x = 0;
        uint32_t start_y = 0;
        while (start_x < height){
            while (start_y < width){
                uint32_t end_x = start_x+8<height?start_x+8:height;
                uint32_t end_y = start_y+8<width?start_y+8:width;
                struct bloc_t *bloc = bloc_create_from_pixels(pixels, start_x, end_x, start_y, end_y);
                struct mcu_t *mcu = mcu_create(bloc, NULL, NULL);
                mcu_current->next = mcu;
                mcu_current = mcu;
                start_y += 8;
            }
            start_x += 8;
            start_y = 0;
        }
    } else {

    }
}