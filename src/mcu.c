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

struct mcu_t *mcu_get_by_id(struct mcu_t *mcu, uint32_t id)
{
	uint32_t i = 0;
	while (i < id && mcu != NULL){
		if (i == id){
			return mcu;
		}
		mcu = mcu->next;
		i++;
	}
	return mcu;
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
struct mcu_t *mcu_create(struct bloc_t *Y, struct bloc_t *Cb, struct bloc_t *Cr){
	struct mcu_t *mcu = calloc(1, sizeof(struct mcu_t));
	mcu->Y = Y;
	mcu->Cb = Cb;
	mcu->Cr = Cr;
	mcu->next = NULL;
	mcu->freqY = NULL;
	mcu->freqCb = NULL;
	mcu->freqCr = NULL;
	mcu->vectorY = NULL;
	mcu->vectorCb = NULL;
	mcu->vectorCr = NULL;
	return mcu;
}

void mcu_destroy(struct mcu_t *mcu){
	blocs_destroy(&mcu->Y);
	blocs_destroy(&mcu->Cb);
	blocs_destroy(&mcu->Cr);
	frequential_blocs_destroy(&mcu->freqY);
	frequential_blocs_destroy(&mcu->freqCb);
	frequential_blocs_destroy(&mcu->freqCr);
	vectors_destroy(&mcu->vectorY);
	vectors_destroy(&mcu->vectorCb);
	vectors_destroy(&mcu->vectorCr);
	free(mcu);
}

void mcus_destroy(struct mcu_t **head){
	struct mcu_t *current = *head;
    while (current != NULL)
    {
        struct mcu_t *next = current->next;
		mcu_destroy(current);
        current = next;
    }

}


void mcu_print(struct mcu_t *mcu){
	printf("MCU:\n");
	printf("----- BLOC -----\n");
	if (mcu->Y != NULL){
		printf("Y:\n");
		blocs_print(mcu->Y);
	}
	if (mcu->Cb != NULL){
		printf("Cb:\n");
		blocs_print(mcu->Cb);
	}
	if (mcu->Cr != NULL){
		printf("Cr:\n");
		blocs_print(mcu->Cr);
	}
	printf("---- FREQ BLOC ----\n");
	if (mcu->freqY != NULL){
		printf("freqY:\n");
		frequential_blocs_print(mcu->freqY);
	}
	if (mcu->freqCb != NULL){
		printf("freqCb:\n");
		frequential_blocs_print(mcu->freqCb);
	}
	if (mcu->freqCr != NULL){
		printf("freqCr:\n");
		frequential_blocs_print(mcu->freqCr);
	}
	printf("----- VECTORS -----\n");
	if (mcu->vectorY != NULL){
		printf("vectorY:\n");
		vectors_print(mcu->vectorY);
	}
	if (mcu->vectorCb != NULL){
		printf("vectorCb:\n");
		vectors_print(mcu->vectorCb);
	}
	if (mcu->vectorCr != NULL){
		printf("vectorCr:\n");
		vectors_print(mcu->vectorCr);
	}
}
void mcus_print(struct mcu_t *mcu){
	while (mcu != NULL){
		mcu_print(mcu);
		mcu = mcu->next;
	}
}

/**
 * @brief apply the subsampling to CB and Cr list of blocs if needed
 * 
 * @param mcu 
 */
void mcu_sous_echantillonne(struct mcu_t *mcu, uint32_t H1, uint32_t V1, uint32_t H2, uint32_t V2, uint32_t H3, uint32_t V3){
	if (H2 < H1 || V2 < V1){
		blocs_fusion(&mcu->Cb, H1, V1, H2, V2);
	}
	if (H3 < H1 || V3 < V1){
		blocs_fusion(&mcu->Cr, H1, V1, H3, V3);
	}
}

void mcus_sous_echantillonne(struct mcu_t *mcu, uint32_t H1, uint32_t V1, uint32_t H2, uint32_t V2, uint32_t H3, uint32_t V3){
	while (mcu != NULL){
		mcu_sous_echantillonne(mcu, H1, V1, H2, V2, H3, V3);
		mcu = mcu->next;
	}
}

/**
 * @brief insert a mcu in a mcu list at the end
 * 
 * @param mcu 
 * @param next 
 */
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
 * @brief Create a list of mcu based on the mcu slicing parameters
 * @test✔️
 * @param pixels matrix of pixels
 * @param height height of the image
 * @param width width of the image
 * @param H1 number of bloc 8x8 horizontally
 * @param V1 number of bloc 8x8 vertically
 * @return struct mcu_t* list of mcu
 */
struct mcu_t* decoupage_mcu(uint8_t **pixels[3], uint32_t height, uint32_t width, uint32_t H1, uint32_t V1){
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
				struct mcu_t *new_mcu = mcu_create(bloc, NULL, NULL);
				mcu_add(&mcus, new_mcu);
				start_x += 8;
			}
			start_y += 8;
			start_x = 0;
		}
	} else {
		uint32_t start_x = 0;
		uint32_t start_y = 0;
		uint32_t *end_x = calloc(H1+1, sizeof(uint32_t));
		uint32_t *end_y = calloc(V1+1, sizeof(uint32_t));
		while (start_y < height){
			while (start_x < width){
				struct bloc_t *blocsR = NULL;
				struct bloc_t *blocsG = NULL;
				struct bloc_t *blocsB = NULL;
				end_x[0] = start_x;
				for (uint32_t i = 1; i < H1+1; i++){
					end_x[i] = start_x+8*i<width?start_x+8*i:width;
				}
				end_y[0] = start_y;
				for (uint32_t i = 1; i < V1+1; i++){
					end_y[i] = start_y+8*i<height?start_y+8*i:height;
				}
	
				for(uint32_t j = 0; j < V1; j++){
					for(uint32_t i = 0; i < H1; i++){
						bloc_add(&blocsR, bloc_create_from_pixels(pixels[0], end_x[i], end_x[i+1], end_y[j], end_y[j+1]));
						bloc_add(&blocsG, bloc_create_from_pixels(pixels[1], end_x[i], end_x[i+1], end_y[j], end_y[j+1]));
						bloc_add(&blocsB, bloc_create_from_pixels(pixels[2], end_x[i], end_x[i+1], end_y[j], end_y[j+1]));
					}
				}
				struct mcu_t *new_mcu = mcu_create(blocsR, blocsG, blocsB);
				mcu_add(&mcus, new_mcu);
				start_x += 8*H1;    
			}
			start_y += 8*V1;
			start_x = 0;
		}
		free(end_x);
		free(end_y);
	}
	return mcus;
}


/**
 * @brief function that apply quantification on each mcu
 * @test✔️
 * @param mcu head of the mcu list
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
 * @brief function that encode each mcu in the bitstream
 * @test✔️
 * @param stream 
 * @param mcu 
 */
void mcu_encode(struct bitstream *stream, struct mcu_t* mcu, 
				struct huff_table *ht_DC_Y,    struct huff_table *ht_AC_Y, 
				struct huff_table *ht_DC_CbCr, struct huff_table *ht_AC_CbCr){
	struct mcu_t *current = mcu;
	int16_t *precY_DC = calloc(1, sizeof(int16_t));
	int16_t *precCb_DC = calloc(1, sizeof(int16_t));
	int16_t *precCr_DC = calloc(1, sizeof(int16_t));
	while (current != NULL){
		*precY_DC = encode_vectors(stream, current->vectorY, *precY_DC, ht_DC_Y, ht_AC_Y);
		*precCb_DC = encode_vectors(stream, current->vectorCb, *precCb_DC, ht_DC_CbCr, ht_AC_CbCr);
		*precCr_DC = encode_vectors(stream, current->vectorCr, *precCr_DC, ht_DC_CbCr, ht_AC_CbCr); 
		vectors_destroy(&current->vectorY);
		current->vectorY = NULL;
		vectors_destroy(&current->vectorCb);
		current->vectorCb = NULL;
		vectors_destroy(&current->vectorCr);
		current->vectorCr = NULL;
		current = current->next;
	}
	free(precY_DC);
	free(precCb_DC);
	free(precCr_DC);
}

/**
 * @brief function that transform each bloc of each mcu into frequential bloc by applying the DCT
 * @test✔️
 * @param mcu head of the mcu list
 */
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
		blocs_destroy(&current->Y);
		current->Y = NULL;
		blocs_destroy(&current->Cb);
		current->Cb = NULL;
		blocs_destroy(&current->Cr);
		current->Cr = NULL;
		current = current->next;
	}
}

/**
 * @brief function that transform each frequential bloc of each mcu into vector with the zigzag order
 * @test✔️
 * @param mcu head of the mcu list
 */
void mcu_zigzag(struct mcu_t* mcu){
	struct mcu_t *current = mcu;
	while (current != NULL){
		struct frequential_bloc_t *current_freq = current->freqY;
		struct vector_t *current_vector = NULL;
		while (current_freq != NULL){
			current_vector = create_vector_from_bloc(current_freq);
			vector_add(&current->vectorY, current_vector);
			current_freq = frequential_bloc_get_next(current_freq);
		}
		current_freq = current->freqCb;
		while (current_freq != NULL){
			current_vector = create_vector_from_bloc(current_freq);
			vector_add(&current->vectorCb, current_vector);
			current_freq = frequential_bloc_get_next(current_freq);
		}
		current_freq = current->freqCr;
		while (current_freq != NULL){
			current_vector = create_vector_from_bloc(current_freq);
			vector_add(&current->vectorCr, current_vector);
			current_freq = frequential_bloc_get_next(current_freq);
		}
		frequential_blocs_destroy(&current->freqY);
		current->freqY = NULL;
		frequential_blocs_destroy(&current->freqCb);
		current->freqCb = NULL;
		frequential_blocs_destroy(&current->freqCr);
		current->freqCr = NULL;
		current = current->next;
	}
}
