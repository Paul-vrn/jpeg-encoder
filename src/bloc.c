/**
 * @file bloc.c
 * @author team 18
 * @brief file containing every functions related to the bloc type and his usage in create MCU and downsampling.
 * @version 0.1
 * @date 2022-05-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include <math.h>

/**
 * @brief structure to represent a bloc containing values of pixels (YCbCr)
 * 
 */
struct bloc_t {
	struct bloc_t *next; /** next bloc*/
	uint8_t matrice[8][8]; /** matrix 8x8 to store values of the bloc */
};

void bloc_set_next(struct bloc_t *bloc, struct bloc_t *next)
{
	bloc->next = next;
}
void bloc_set_matrice(struct bloc_t *bloc, uint8_t matrice[8][8]){
	for (uint32_t i = 0; i < 8; i++){
		for (uint32_t j = 0; j < 8; j++){
			bloc->matrice[i][j] = matrice[i][j];
		}
	}
}

struct bloc_t *bloc_get_next(struct bloc_t *bloc){
	return bloc->next;
}
uint8_t bloc_get_matrice(struct bloc_t *bloc, uint32_t i, uint32_t j){
	return bloc->matrice[i][j];
}

/**
 * @brief add the bloc to the bloc list at the end
 * 
 * @param bloc 
 * @param next 
 */
void bloc_add(struct bloc_t **bloc, struct bloc_t *next){
	struct bloc_t *tmp = *bloc;
	if (tmp == NULL){
		*bloc = next;
	} else {
		while (tmp->next != NULL){
			tmp = tmp->next;
		}
		tmp->next = next;
	}
}


/**
 * @brief Create a bloc
 * @test✔️
 * @param matrice The matrice of the bloc
 * @return struct bloc_t* The bloc
 */
struct bloc_t *bloc_create(uint8_t matrice[8][8]){
	struct bloc_t *bloc = calloc(1, sizeof(struct bloc_t));
	bloc->next = NULL;
	if (matrice != NULL){
		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 8; j++){
				//printf("%u\n", matrice[i][j]);
				bloc->matrice[i][j] = matrice[i][j];
			}
		}
	} else {
		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 8; j++){
				bloc->matrice[i][j] = 0;
			}
		}
	}
	return bloc;
}

/**
 * @brief function to create a bloc from a set of pixels
 * @test✔️
 * @param pixels matrix containing ALL the pixels
 * @param start_x x coordinate of the first pixel
 * @param end_x x coordinate of the last pixel
 * @param start_y y coordinate of the first pixel
 * @param end_y y coordinate of the last pixel
 * @return struct bloc_t* pointer to the new bloc
 */
struct bloc_t* bloc_create_from_pixels(uint8_t **pixels, uint32_t start_x, uint32_t end_x, uint32_t start_y, uint32_t end_y){
	struct bloc_t *bloc = calloc(1, sizeof(struct bloc_t));
	bloc->next = NULL;
	uint32_t k = 0;
	uint32_t l = 0;
	/* place pixels in the bloc */
	for (uint32_t i = start_y; i < end_y; i++){
		for (uint32_t j = start_x; j < end_x; j++){
			bloc->matrice[k][l] = pixels[i][j];
			l++;
		}
		k++;
		l = 0;
	}
	if (end_x-start_x==8 && end_y-start_y==8){
		return bloc;
	} /* else the range of pixels is smaller than 8, so we must fill the rest of the bloc*/
	k = 0;
	l = end_x - start_x;
	for (uint32_t i = start_y; i < end_y; i++){ 
		for (uint32_t j = end_x; j < start_x + 8; j++){
			bloc->matrice[k][l] = pixels[i][end_x-1];
			l++;
		}
		k++;
		l = end_x - start_x;
	}

	k = end_y - start_y;
	l = 0;
	for (uint32_t i = end_y; i < start_y + 8; i++){
		for (uint32_t j = start_x; j < start_x+8; j++){
			if (j < end_x){
				bloc->matrice[k][l] = pixels[end_y-1][j];
			} else {
				bloc->matrice[k][l] = pixels[end_y-1][end_x-1];
			}
			l++;
		}
		k++;
		l = 0;
	}
	return bloc;
}

/**
 * @brief Destroy blocs in the list
 * @test✔️
 * @param blocs 
 */
void blocs_destroy(struct bloc_t **head){
	struct bloc_t *current = *head;
	while (current != NULL) {
		struct bloc_t *next = current->next;
		free(current);
		current = next;
	}
}

/**
 * @brief Print values of a bloc
 * @test✔️
 * @param bloc 
 */
void bloc_print(struct bloc_t *bloc){
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			printf("%x ", bloc->matrice[i][j]);
		}
		printf("\n");
	}
}

/**
 * @brief Print values of blocs in the list
 * @test✔️
 * @param blocs
 */
void blocs_print(struct bloc_t *blocs){
	struct bloc_t *bloc = blocs;
	while (bloc != NULL) {
		bloc_print(bloc);
		bloc = bloc->next;
		printf("\n");
	}
}


/**
 * @brief function that merge blocs based on the sous echantillonage part,
 * @test✔️
 * @param blocs 
 */
void blocs_fusion(struct bloc_t **blocs, uint32_t H1, uint32_t V1, uint32_t H2, uint32_t V2){
	uint8_t big_matrix[8*V1][8*H1];
	struct bloc_t *current_bloc = *blocs;

	/* Create a big matrix of size H1xV1, containing every blocs side by side*/
	for (uint32_t i = 0; i < V1; i++) {
		for (uint32_t j = 0; j < H1; j++) {
			for(uint32_t k = 0; k < 8; k++) {
				for(uint32_t l = 0; l < 8; l++) {
					big_matrix[i*8+k][j*8+l] = current_bloc->matrice[k][l];
				}
			}
			current_bloc = current_bloc->next;
		}
	}
	uint32_t value = 0;
	V1 = (uint8_t) V1/V2;
	H1 = (uint8_t) H1/H2;
	/* Create a new matrix H2xV2, where the downsampling is operated */
	uint8_t **downsampling_matrix = calloc(V2*8, sizeof(uint8_t*));
	for (uint32_t i = 0; i < V2*8; i++) {
		downsampling_matrix[i] = calloc(H2*8, sizeof(uint8_t));
		for (uint32_t j = 0; j < H2*8; j++) {
			value = 0;
			for (uint32_t k = i*V1; k < (i*V1+V1); k++) {
				for (uint32_t l = j*H1; l < (j*H1+H1); l++) {
					value += big_matrix[k][l];
				}
			}
			value = value/(V1*H1);
			downsampling_matrix[i][j] = (uint8_t) value;
		}
	}
	struct bloc_t *bloc_fusion = NULL;
	/* Create blocs from the small matrix */
	for (uint32_t i = 0; i < V2; i++) {
		for (uint32_t j = 0; j < H2; j++) {
			bloc_add(&bloc_fusion, bloc_create_from_pixels(downsampling_matrix, j*8, j*8+8, i*8, i*8+8));
		}
	}
	for(uint32_t i = 0; i < V2*8; i++) {
		free(downsampling_matrix[i]);
	}
	free(downsampling_matrix);
	blocs_destroy(blocs);
	*blocs = bloc_fusion;

}
