#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <jpeg_writer.h>

/* Type opaque représentant un arbre de Huffman. */
struct huffman_table;

struct code;
/*
    Construit un arbre de Huffman à partir d'une table
    de symboles comme présenté en section 
    "Compression d'un bloc fréquentiel -> Le codage de Huffman" du sujet.
    nb_symb_per_lengths est un tableau contenant le nombre
    de symboles pour chaque longueur de 1 à 16,
    symbols est le tableau  des symboles ordonnés,
    et nb_symbols représente la taille du tableau symbols.
*/
struct huff_table *huffman_table_build_moi(uint8_t *nb_symb_per_lengths,
                                              uint8_t *symbols,
                                              uint8_t nb_symbols);

bool recursif_moi(struct node *currentNode, uint32_t code, uint32_t depth, uint32_t huffcode_table, uint32_t *index);

uint32_t huffcode_table_build_moi(struct huffman_table *hufftable);

/*
    Retourne le chemin dans l'arbre ht permettant d'atteindre
    la feuille de valeur value. nb_bits est un paramètre de sortie
    permettant de stocker la longueur du chemin retourné.
*/

uint32_t huffman_table_get_path_moi(struct huff_table *ht,
                                       uint8_t value,
                                       uint8_t *nb_bits);

/*
   Retourne le tableau des symboles associé à l'arbre de
   Huffman passé en paramètre.
*/
uint8_t *huffman_table_get_symbols_moi(struct huff_table *ht);

/*
    Retourne le tableau du nombre de symboles de chaque longueur
    associé à l'arbre de Huffman passé en paramètre.
*/
uint8_t *huffman_table_get_length_vector_moi(struct huff_table *ht);

/*
    Détruit l'arbre de Huffman passé en paramètre et libère
    toute la mémoire qui lui est associée.
*/
void huffman_table_destroy_moi  (struct huff_table *ht);

#endif /* HUFFMAN_H */
