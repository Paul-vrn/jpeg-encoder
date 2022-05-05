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

void mcu_set_next(struct mcu_t *mcu, struct mcu_t *next)
{
    mcu->next = next;
}
void mcu_set_Y(struct mcu_t *mcu, struct bloc_t *Y)
{
    mcu->Y = Y;
}
void mcu_set_Cb(struct mcu_t *mcu, struct bloc_t *Cb)
{
    mcu->Cb = Cb;
}
void mcu_set_Cr(struct mcu_t *mcu, struct bloc_t *Cr)
{
    mcu->Cr = Cr;
}
struct bloc_t* mcu_get_Y(struct mcu_t *mcu)
{
    return mcu->Y;
}
struct bloc_t* mcu_get_Cb(struct mcu_t *mcu)
{
    return mcu->Cb;
}
struct bloc_t* mcu_get_Cr(struct mcu_t *mcu)
{
    return mcu->Cr;
}
struct mcu_t* mcu_get_next(struct mcu_t *mcu)
{
    return mcu->next;
}

/**
 * @brief 
 * 
 * @param Y 
 * @param Cb 
 * @param Cr 
 * @return struct mcu_t* 
 */
struct mcu_t *mcu_create(struct bloc_t *Y, struct bloc_t *Cb, struct bloc_t *Cr){
    struct mcu_t *mcu = calloc(1, sizeof(struct mcu_t));
    mcu->Y = Y;
    mcu->Cb = Cb;
    mcu->Cr = Cr;
    mcu->next = NULL;
    return mcu;
}

/**
 * @brief destroy mcu
 * @test✔️
 * @param mcu
 */
void mcu_destroy(struct mcu_t *mcu){
    if (mcu->Y != NULL)
        blocs_destroy(mcu->Y);
    if (mcu->Cb != NULL)
        blocs_destroy(mcu->Cb);
    if (mcu->Cr != NULL)
        blocs_destroy(mcu->Cr);
    free(mcu);
}


void mcu_print(struct mcu_t *mcu){
    printf("MCU:\n");
    printf("Y:\n");
    blocs_print(mcu->Y);
    printf("Cb:\n");
    blocs_print(mcu->Cb);
    printf("Cr:\n");
    blocs_print(mcu->Cr);
}

/**
 * @brief 
 * 
 * @param mcu 
 */
void mcu_sous_echantillonne(struct mcu_t *mcu){
    blocs_fusion(&mcu->Cb);
    blocs_fusion(&mcu->Cr);
}

/**
 * @brief 
 * 
 * @param pixels 
 * @param height 
 * @param width 
 * @param gris 
 * @return struct mcu_t* 
 */
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
    return mcu_current;
}