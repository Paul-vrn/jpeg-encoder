#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "bloc.h"
#include "frequential_bloc.h"
#include "vector.h"
#include "bitstream.h"
#include "jpeg_writer.h"
#include "encoding.h"

struct mcu_t {
    struct bloc_t *Y;
    struct bloc_t *Cb;
    struct bloc_t *Cr;
    struct frequential_bloc_t *freqY;
    struct frequential_bloc_t *freqCb;
    struct frequential_bloc_t *freqCr;
    struct vector_t *vectorY;
    struct vector_t *vectorCb;
    struct vector_t *vectorCr;
    struct mcu_t *next;
    uint32_t largeur;
    uint32_t hauteur;
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
void mcu_set_largeur(struct mcu_t *mcu, uint32_t largeur)
{
    mcu->largeur = largeur;
}
void mcu_set_hauteur(struct mcu_t *mcu, uint32_t hauteur)
{
    mcu->hauteur = hauteur;
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
struct vector_t* mcu_get_vectorY(struct mcu_t *mcu)
{
    return mcu->vectorY;
}
struct vector_t* mcu_get_vectorCb(struct mcu_t *mcu)
{
    return mcu->vectorCb;
}
struct vector_t* mcu_get_vectorCr(struct mcu_t *mcu)
{
    return mcu->vectorCr;
}

uint32_t mcu_count(struct mcu_t *mcu)
{
    uint32_t count = 0;
    while (mcu != NULL) {
        count++;
        mcu = mcu->next;
    }
    return count;
}
/**
 * @brief Create a mcu
 * @test✔️
 * @param Y (bloc_t*) The Y bloc
 * @param Cb (bloc_t*) The Cb bloc
 * @param Cr (bloc_t*) The Cr bloc
 * @return struct mcu_t* 
 */
struct mcu_t *mcu_create(struct bloc_t *Y, struct bloc_t *Cb, struct bloc_t *Cr, uint32_t largeur, uint32_t hauteur){
    struct mcu_t *mcu = calloc(1, sizeof(struct mcu_t));
    mcu->Y = Y;
    mcu->Cb = Cb;
    mcu->Cr = Cr;
    mcu->next = NULL;
    mcu->freqY = NULL;
    mcu->freqCb = NULL;
    mcu->freqCr = NULL;
    mcu->largeur = largeur;
    mcu->hauteur = hauteur;
    return mcu;
}

/**
 * @brief destroy mcu
 * @test✔️
 * @param mcu
 */
void mcu_destroy(struct mcu_t *mcu){
    blocs_destroy(mcu->Y);
    blocs_destroy(mcu->Cb);
    blocs_destroy(mcu->Cr);
    frequential_blocs_destroy(mcu->freqY);
    frequential_blocs_destroy(mcu->freqCb);
    frequential_blocs_destroy(mcu->freqCr);
    vectors_destroy(mcu->vectorY);
    vectors_destroy(mcu->vectorCb);
    vectors_destroy(mcu->vectorCr);
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
void mcus_print(struct mcu_t *mcu){
    while (mcu != NULL){
        mcu_print(mcu);
        mcu = mcu->next;
    }
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

void mcu_add(struct mcu_t **mcu, struct mcu_t *next){
    struct mcu_t *tmp = *mcu;
    if (tmp == NULL){
        *mcu = next;
    }
    else{
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = next;
    }
}
/**
 * @brief 
 * @test✔️(gris) ✔️(RGB 4:4:4) ✔️(RGB 4:2:2) ~✔️(RGB 4:2:0)
 * @param pixels 
 * @param height 
 * @param width 
 * @param gris 
 * @return struct mcu_t* 
 */
struct mcu_t* decoupage_mcu(uint8_t **pixels[3], uint32_t height, uint32_t width, uint32_t H1, uint32_t H2, uint32_t H3, uint32_t V1, uint32_t V2, uint32_t V3){
    
    struct mcu_t *mcus = NULL;
    if (pixels[1] == NULL){
        //MCU 8x8
        uint32_t start_x = 0;
        uint32_t start_y = 0;
        while (start_y < height){
            while (start_x < width){
                uint32_t end_x = start_x+8<width?start_x+8:width;
                uint32_t end_y = start_y+8<height?start_y+8:height;
                struct bloc_t *bloc = bloc_create_from_pixels(pixels[0], start_x, end_x, start_y, end_y);
                struct mcu_t *new_mcu = mcu_create(bloc, NULL, NULL, 8, 8);
                mcu_add(&mcus, new_mcu);
                start_x += 8;
            }
            start_y += 8;
            start_x = 0;
        }
    } else {
        if (H1 == 2 && V1 == 2 && H2 == 2 && V2 == 2 && H3 == 2 && V3 == 2 ){ // tested
            //MCU 8x8
            uint32_t start_x = 0;
            uint32_t start_y = 0;
            while (start_y < height){
                while (start_x < width){
                    uint32_t end_x = start_x+8<width?start_x+8:width;
                    uint32_t end_y = start_y+8<height?start_y+8:height;
                    struct bloc_t *blocR = bloc_create_from_pixels(pixels[0], start_x, end_x, start_y, end_y);
                    struct bloc_t *blocG = bloc_create_from_pixels(pixels[1], start_x, end_x, start_y, end_y);
                    struct bloc_t *blocB = bloc_create_from_pixels(pixels[2], start_x, end_x, start_y, end_y);
                    struct mcu_t *new_mcu = mcu_create(blocR, blocG, blocB, 8, 8);
                    mcu_add(&mcus, new_mcu);
                    start_x += 8;
                }
                start_y += 8;
                start_x = 0;
            }
        } else if (H1 == 2 && V1 == 2 && H2 == 1 && V2 == 2 && H3 == 1 && V3 == 2){ // not work
            //MCU 16x8
            printf("test");
            uint32_t start_x = 0;
            uint32_t start_y = 0;
            while (start_y < height){
                while (start_x < width){
                    uint32_t end_x1 = start_x+8<width?start_x+8:width;
                    uint32_t end_x2 = start_x+16<width?start_x+16:width;
                    uint32_t end_y = start_y+8<height?start_y+8:height;
                    struct bloc_t *blocR = bloc_create_from_pixels(pixels[0], start_x, end_x1, start_y, end_y);
                    struct bloc_t *blocG = bloc_create_from_pixels(pixels[1], start_x, end_x1, start_y, end_y);
                    struct bloc_t *blocB = bloc_create_from_pixels(pixels[2], start_x, end_x1, start_y, end_y);
                    bloc_add(&blocR, bloc_create_from_pixels(pixels[0], end_x1, end_x2, start_y, end_y));
                    bloc_add(&blocG, bloc_create_from_pixels(pixels[1], end_x1, end_x2, start_y, end_y));
                    bloc_add(&blocB, bloc_create_from_pixels(pixels[2], end_x1, end_x2, start_y, end_y));
                    struct mcu_t *new_mcu = mcu_create(blocR, blocG, blocB, 16, 8);
                    mcu_add(&mcus, new_mcu);
                    start_x += 16;
                }
                start_y += 8;
                start_x = 0;
            }
        } else if (H1 == 2 && V1 == 2 && H2 == 1 && V2 == 1 && H3 == 1 && V3 == 1){
            //MCU 16x16
            uint32_t start_x = 0;
            uint32_t start_y = 0;
            while (start_y < height){
                while (start_x < width){
                    uint32_t end_x1 = start_x+8<width?start_x+8:width;
                    uint32_t end_x2 = start_x+16<width?start_x+16:width;
                    uint32_t end_y1 = start_y+8<height?start_y+8:height;
                    uint32_t end_y2 = start_y+16<height?start_y+16:height;
                    struct bloc_t *blocR = bloc_create_from_pixels(pixels[0], start_x, end_x1, start_y, end_y1);
                    struct bloc_t *blocG = bloc_create_from_pixels(pixels[1], start_x, end_x1, start_y, end_y1);
                    struct bloc_t *blocB = bloc_create_from_pixels(pixels[2], start_x, end_x1, start_y, end_y1);
            
                    bloc_add(&blocR, bloc_create_from_pixels(pixels[0], end_x1, end_x2, start_y, end_y1));
                    bloc_add(&blocG, bloc_create_from_pixels(pixels[1], end_x1, end_x2, start_y, end_y1));
                    bloc_add(&blocB, bloc_create_from_pixels(pixels[2], end_x1, end_x2, start_y, end_y1));
            
                    bloc_add(&blocR, bloc_create_from_pixels(pixels[0], start_x, end_x1, end_y1, end_y2));
                    bloc_add(&blocG, bloc_create_from_pixels(pixels[1], start_x, end_x1, end_y1, end_y2));
                    bloc_add(&blocB, bloc_create_from_pixels(pixels[2], start_x, end_x1, end_y1, end_y2));
            
                    bloc_add(&blocR, bloc_create_from_pixels(pixels[0], end_x1, end_x2, end_y1, end_y2));
                    bloc_add(&blocG, bloc_create_from_pixels(pixels[1], end_x1, end_x2, end_y1, end_y2));
                    bloc_add(&blocB, bloc_create_from_pixels(pixels[2], end_x1, end_x2, end_y1, end_y2));
                    struct mcu_t *new_mcu = mcu_create(blocR, blocG, blocB, 16, 16);
                    mcu_add(&mcus, new_mcu);
                    start_x += 16;
                }
                start_y += 16;
                start_x = 0;
            }
        } else {
            printf("Error: unsupported MCU size\n");
        }
    }
    return mcus;
}

/**
 * @brief 
 * 
 * @param mcu 
 */
void mcu_quantification(struct mcu_t *mcu){
    struct mcu_t *current_mcu = mcu;
    while (current_mcu != NULL){
        vectors_quantificationY(current_mcu->vectorY);
        vectors_quantificationCbCr(current_mcu->vectorCb);
        vectors_quantificationCbCr(current_mcu->vectorCr);
        current_mcu = current_mcu->next;
    }
}

/**
 * @brief Encode vectors in the stream
 * @test 
 * @param stream 
 * @param mcu 
 */
void mcu_encode(struct bitstream *stream, struct mcu_t* mcu){
    struct mcu_t *current = mcu;
    int16_t *precY_DC = calloc(1, sizeof(int16_t));
    int16_t *precCb_DC = calloc(1, sizeof(int16_t));
    int16_t *precCr_DC = calloc(1, sizeof(int16_t));
    while (current != NULL){
        *precY_DC = encode_vectors(stream, current->vectorY, Y, *precY_DC);
        *precCb_DC = encode_vectors(stream, current->vectorCb, Cb, *precCb_DC);
        *precCr_DC = encode_vectors(stream, current->vectorCr, Cr, *precCr_DC);        
        current = current->next;
    }
}

void mcu_dct(struct mcu_t* mcu){
    struct mcu_t *current = mcu;
    while (current != NULL){
        struct bloc_t *current_bloc = current->Y;
        struct frequential_bloc_t *current_freq = NULL;
        while (current_bloc != NULL){
            current_freq = dct(current_bloc);
            frequential_bloc_add(&current->freqY, current_freq);
            current_bloc = bloc_get_next(current_bloc);
        }
        current_bloc = current->Cb;
        while (current_bloc != NULL){
            current_freq = dct(current_bloc);
            frequential_bloc_add(&current->freqCb, current_freq);
            current_bloc = bloc_get_next(current_bloc);
        }
        current_bloc = current->Cr;
        while (current_bloc != NULL){
            current_freq = dct(current_bloc);
            frequential_bloc_add(&current->freqCr, current_freq);
            current_bloc = bloc_get_next(current_bloc);
        }
        current = current->next;
    }
}

void mcu_zigzag(struct mcu_t* mcu){
    struct mcu_t *current = mcu;
    while (current != NULL){
        struct frequential_bloc_t *current_freq = current->freqY;
        struct vector_t *current_vector = NULL;
        while (current_freq != NULL){
            current_vector = create_vector_from_bloc2(current_freq);
            vector_add(&current->vectorY, current_vector);
            current_freq = frequential_bloc_get_next(current_freq);
        }
        current_freq = current->freqCb;
        while (current_freq != NULL){
            current_vector = create_vector_from_bloc2(current_freq);
            vector_add(&current->vectorCb, current_vector);
            current_freq = frequential_bloc_get_next(current_freq);
        }
        current_freq = current->freqCr;
        while (current_freq != NULL){
            current_vector = create_vector_from_bloc2(current_freq);
            vector_add(&current->vectorCr, current_vector);
            current_freq = frequential_bloc_get_next(current_freq);
        }
        current = current->next;
    }
}
