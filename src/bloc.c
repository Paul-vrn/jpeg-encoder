#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include <math.h>

/**
 * @brief strcture to represent a bloc containing values of pixels (YCbCr)
 * 
 */
struct bloc_t {
	struct bloc_t *next;
	uint8_t matrice[8][8];
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
	}
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
	uint8_t res[8*V1][8*H1];
	struct bloc_t *current_bloc = *blocs;

	for (uint32_t i = 0; i < V1; i++) {
		for (uint32_t j = 0; j < H1; j++) {
			for(uint32_t k = 0; k < 8; k++) {
				for(uint32_t l = 0; l < 8; l++) {
					res[i*8+k][j*8+l] = current_bloc->matrice[k][l];
				}
			}
			current_bloc = current_bloc->next;
		}
	}
	uint32_t value = 0;
	V1 = (uint8_t) V1/V2;
	H1 = (uint8_t) H1/H2;
	uint8_t **res2 = calloc(V2*8, sizeof(uint8_t*));
	for (uint32_t i = 0; i < V2*8; i++) {
		res2[i] = calloc(H2*8, sizeof(uint8_t));
		for (uint32_t j = 0; j < H2*8; j++) {
			value = 0;
			for (uint32_t k = i*V1; k < (i*V1+V1); k++) {
				for (uint32_t l = j*H1; l < (j*H1+H1); l++) {
					value += res[k][l];
				}
			}
			value = value/(V1*H1);
			res2[i][j] = (uint8_t) value;
		}
	}
	struct bloc_t *bloc_fusion = NULL;
	for (uint32_t i = 0; i < V2; i++) {
		for (uint32_t j = 0; j < H2; j++) {
			bloc_add(&bloc_fusion, bloc_create_from_pixels(res2, j*8, j*8+8, i*8, i*8+8));
		}
	}
	for(uint32_t i = 0; i < V2*8; i++) {
		free(res2[i]);
	}
	free(res2);
	blocs_destroy(blocs);
	*blocs = bloc_fusion;

}

/**
 * @brief compare two blocs 
 * @test✔️
 * @param bloc1 
 * @param bloc2 
 * @return true if blocs are equal, false otherwise
 */
bool compare_blocs(struct bloc_t *bloc1, struct bloc_t *bloc2){
	for (uint32_t i = 0; i < 8; i++) {
		for (uint32_t j = 0; j < 8; j++) {
			if (bloc1->matrice[i][j] != bloc2->matrice[i][j]){
				return false;
			}
		}
	} 
	return true;
}