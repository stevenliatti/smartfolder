/**
 * @file hash_table.c
 * @brief      Gestion d'une table de hachage.
 * @author     Steven Liatti et Matthieu Constant
 * @bug        Pas de bugs connus
 * @date       Janvier 2017
 * @version    1.0
 */

#include "hash_table.h"

/**
 * @brief      Initialisation d'un nouvelle table de hash, avec sa taille
 *             initiale et son facteur de remplissage.
 *
 * @param[in]  capacity     La taille initiale.
 * @param[in]  load_factor  Le facteur de charge.
 *
 * @return     Un pointeur sur une hash_table_t.
 */
hash_table_t* init(unsigned int capacity, double load_factor) {
	int real_capacity = closest_prime_number(capacity, true);
	hash_table_t* hash_table = malloc(sizeof(hash_table_t));
	hash_table->table = malloc(sizeof(string_t) * real_capacity);
	hash_table->capacity = real_capacity;
	hash_table->elements_count = 0;
	hash_table->load_factor = load_factor;
	for (int i = 0; i < real_capacity; i++) {
		hash_table->table[i].state = freed;
	}
	return hash_table;
}

/**
 * @brief      Si le taux de remplissage dépasse le facteur de charge, crée une
 *             nouvelle table de taille selon GROWTH_FACTOR et replace les
 *             éléments dedans.
 *
 * @param      hash_table  La table de hash à redimensionner.
 *
 * @return     La nouvelle table dimensionnée, avec tous les éléments de
 *             l'ancienne.
 */
hash_table_t* resize(hash_table_t* hash_table) {
	logger(LOG_DEBUG_DONE, stderr, "in resize\n");
	bool inserted;
	hash_table_t* new_hash_table = init((int) (GROWTH_FACTOR * (double) hash_table->capacity), hash_table->load_factor);
	for (int i = 0; i < hash_table->capacity; i++) {
		if (hash_table->table[i].state != freed) {
			insert(hash_table->table[i].string, new_hash_table, &inserted);
		}
	}
	free_table(hash_table);
	logger(LOG_DEBUG_DONE, stderr, "resize success\n");
	return new_hash_table;
}

/**
 * @brief      Teste si la chaine string est contenue dans la table de hash
 *             hash_table.
 *
 * @param      string      La chaine de caractères, un pointeur sur char.
 * @param      hash_table  La table de hash.
 * @param      hash_r      Retourne la position ou devrait se trouver l'élément
 *                         s'il est absent de la table (pour une insertion plus
 *                         rapide par la suite par exemple).
 *
 * @return     Vrait si l'élément est dans la table, faux sinon.
 */
bool contains(char* string, hash_table_t* hash_table, int* hash_r) {
	logger(LOG_DEBUG_DONE, stderr, "in contains, capacity : %d\n", hash_table->capacity);
	int hash = simple_hash(string, hash_table->capacity);

	while(hash_table->table[hash].state != freed) {
		if (strcmp(hash_table->table[hash].string, string) == 0 && hash_table->table[hash].state == occupied) {
			logger(LOG_DEBUG_DONE, stderr, "contains %s\n", string);
			*hash_r = hash;
			return true;
		}
		hash = simple_and_double_hash(hash, string, hash_table->capacity);
	}
	*hash_r = hash;
	return false;
}

/**
 * @brief      Fonction insérant la chaine de caractères en argument dans la
 *             table de hash, selon un hash fourni (calculé auparavant). Insère
 *             uniquement si l'élément est absent de la table.
 *
 * @param      string      La chaine de caractères.
 * @param      hash_table  La table de hash.
 * @param      inserted    Un pointeur sur boolean indiquant s'il y a eu
 *                         insertion ou pas.
 * @param      hash        Le hash calcul au préalable.
 *
 * @return     La table de hash avec ou sans l'élément inséré.
 */
hash_table_t* insert_with_hash(char* string, hash_table_t* hash_table, bool* inserted, int* hash) {
	if ((double) hash_table->elements_count / (double) hash_table->capacity > hash_table->load_factor) {
		hash_table = resize(hash_table);
	}
	logger(LOG_DEBUG_DONE, stderr, "in insert_with_hash, capacity : %d\n", hash_table->capacity);
	
	if (*hash < 0 && contains(string, hash_table, hash)) {
		logger(LOG_DEBUG_DONE, stderr, "NOT insert %s\n", string);
		*inserted = false;
		return hash_table;
	}
	logger(LOG_DEBUG_DONE, stderr, "hash calculated by contains : %d\n", *hash);
	hash_table->table[*hash].string = malloc(sizeof(char) * (strlen(string) + 1));
	strcpy(hash_table->table[*hash].string, string);
	hash_table->table[*hash].state = occupied;
	hash_table->elements_count++;
	logger(LOG_DEBUG_DONE, stderr, "insert %s\n", string);
	*inserted = true;
	return hash_table;
}
/**
 * @brief      Comportement similaire à insert_with_hash, mais en calculant le
 *             hash en interne.
 *
 * @param      string      La chaine de caractères.
 * @param      hash_table  La table de hash.
 * @param      inserted    Un pointeur sur boolean indiquant s'il y a eu
 *                         insertion ou pas.
 *
 * @return     La table de hash avec ou sans l'élément inséré.
 */
hash_table_t* insert(char* string, hash_table_t* hash_table, bool* inserted) {
	int hash = -1;
	logger(LOG_DEBUG_DONE, stderr, "in insert, capacity : %d\n", hash_table->capacity);
	return insert_with_hash(string, hash_table, inserted, &hash);
}

/**
 * @brief      Libère la mémoire occupée par une table de hash.
 *
 * @param      hash_table  Un pointeur sur une table de hash.
 */
void free_table(hash_table_t* hash_table) {
	for (int i = 0; i < hash_table->capacity; i++) {
		free(hash_table->table[i].string);
	}
	free(hash_table->table);
	free(hash_table);
}

void print_table(hash_table_t* hash_table) {
	for (int i = 0; i < hash_table->capacity; i++) {
		logger(LOG_DEBUG_DONE, stderr, "%s - %s\n", hash_table->table[i].string, hash_table->table[i].state == freed ? "freed" : "not freed");
	}
}
