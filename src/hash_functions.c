/**
 * @file hash_functions.c
 * @brief      Série de fonctions utilitaires pour le calcul d'un hash.
 * @author     Steven Liatti
 * @bug        Pas de bugs connus
 * @date       Janvier 2017
 * @version    1.0
 */

#include "hash_functions.h"

/**
 * @brief      Détermine si number est premier ou non.
 *
 * @param[in]  number  Un nombre entier positif.
 *
 * @return     Vrai si premier, faux sinon.
 */
bool is_prime(unsigned int number) {
	// Tester de 2 jusqu'à la racine carrée de number.
	int limit = ((int) sqrt(number)) + 1;
	bool is_prime = true;
	
	if (number == 0 || number == 1)
		return false;

	if (number == 2)
		return true;
	
	for (int i = 2; i <= limit; i++) {
		if (number % i == 0)
			is_prime = false;
	}
	logger(LOG_DEBUG_DONE, stderr, "is_prime return : (%d) %d\n", number, is_prime);
	return is_prime;
}

/**
 * @brief      Retourne le nombre premier strictement plus grand ou plus petit
 *             que le nombre donné.
 *
 * @param[in]  number  Un nombre entier positif.
 * @param[in]  higher  Si vrai, retourne le premier strictement plus grand.
 *                     Sinon, le plus petit.
 *
 * @return     Le nombre premier le plus proche de number.
 */
unsigned int closest_prime_number(unsigned int number, bool higher) {
	unsigned int i = number;
	if (higher) {
		do {
			i++;
		} while (!is_prime(i));
	}
	else {
		do {
			i--;
		} while (!is_prime(i) && i > 1);
	}
	logger(LOG_DEBUG_DONE, stderr, "closest_prime_number return : %d\n", i);
	return i;
}

/**
 * @brief      Calcule le hash d'un string en fonction de la taille d'une table
 *             de hash. La somme de la valeur ascii modulo la taille de la
 *             table.
 *
 * @param      string         La chaine de caractères, un pointeur sur char.
 * @param[in]  size_of_table  La taille d'une table de hash.
 *
 * @return     La position dans une table de hash.
 */
unsigned int simple_hash(char* string, unsigned int size_of_table) {
	unsigned int hash = 0;
	for(int i = 0; i < (int) strlen(string); i++)
		hash = hash + string[i];

	logger(LOG_DEBUG_DONE, stderr, "simple_hash return : %d, %d\n", hash, hash % size_of_table);
	return hash % size_of_table;
}

/**
 * @brief      Recalcule un hash à partir du simple hash, lors d'une collision
 *             par exemple.
 *
 * @param      string         La chaine de caractères, un pointeur sur char.
 * @param[in]  size_of_table  La taille d'une table de hash.
 *
 * @return     Une nouvelle position dans la table de hash.
 */
unsigned int double_hash(char* string, unsigned int size_of_table) {
	unsigned int i = 1 + (simple_hash(string, size_of_table) % closest_prime_number(size_of_table, false));
	logger(LOG_DEBUG_DONE, stderr, "double_hash return : %d\n", i);
	return i;
}

/**
 * @brief      Opère le simple et le double hash sur un string.
 *
 * @param[in]  simple_hash    Le simple hash calculé auparavant.
 * @param      string         La chaine de caractères, un pointeur sur char.
 * @param[in]  size_of_table  La taille d'une table de hash.
 *
 * @return     Une nouvelle position dans la table de hash.
 */
unsigned int simple_and_double_hash(unsigned int simple_hash, char* string, unsigned int size_of_table) {
	unsigned int i = (simple_hash + double_hash(string, size_of_table)) % size_of_table;
	logger(LOG_DEBUG_DONE, stderr, "simple_and_double_hash return : %d\n", i);
	return i;
}
