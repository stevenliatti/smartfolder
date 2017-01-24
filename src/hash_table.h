/**
 * @file hash_table.h
 * @brief      Header de la gestion d'une table de hachage.
 * @author     Steven Liatti et Matthieu Constant
 * @bug        Pas de bugs connus
 * @date       Janvier 2017
 * @version    1.0
 */

#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include "wrapper.h"
#include "hash_functions.h"

#define CAPACITY 10
#define LOAD_FACTOR 0.75
#define GROWTH_FACTOR 2.0

/**
 * @brief      Énumération des différents états possibles d'un élément dans une
 *             table de hash.
 */
enum state_t {
	freed, /*!< Libre */
	occupied, /*!< Occupé */
	deleted /*!< Supprimé (pas utilisé dans ce TP) */
};

/**
 * @struct string_t hash_table.h
 * @brief      Structure définissant un élément string dans la table.
 */
typedef struct {
	char* string; /*!< La valeur du string */
	enum state_t state; /*!< L'état de l'élément (la case) */
} string_t;

/**
 * @struct hash_table_t hash_table.h
 * @brief      Structure définissant une table de hash.
 */
typedef struct {
	string_t* table; /*!< Un tableau d'éléments string */
	int capacity; /*!< La taille de la table */
	int elements_count; /*!< Le nombre d'éléments internes */
	double load_factor; /*!< Le facteur de charge */
} hash_table_t;

hash_table_t* init(unsigned int capacity, double load_factor);
bool contains(char* string, hash_table_t* hash_table, int* hash);
hash_table_t* insert_with_hash(char* string, hash_table_t* hash_table, bool* inserted, int* hash);
hash_table_t* insert(char* string, hash_table_t* hash_table, bool* inserted);
void free_table(hash_table_t* hash_table);
void print_table(hash_table_t* hash_table);

#endif
