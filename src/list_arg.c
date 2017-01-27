/**
 * @file list_arg.c
 * @brief      Implémentation des fonctions permettant la gestion d'une
 *             liste/pile d'arguments à parser.
 * @author     Steven Liatti et Matthieu Constant
 * @bug        Pas de bugs connus
 * @date       Janvier 2017
 * @version    1.0
 */

#include "list_arg.h"

/**
 * Fonction retournant une nouvelle liste vide.
 *
 * @return     pointeur sur la nouvelle liste.
 */
list_arg_t* larg_new_list() {
	return NULL;
}

/**
 * Fonction retournant true si une liste est vide.
 *
 * @param      list  une list_arg_t*.
 *
 * @return     true si une liste est vide, false sinon.
 */
bool larg_is_empty(const list_arg_t* list) {
	return list == NULL;
}

/**
 * Fonction insérant en tête d'une liste <list> les données <value>.
 *
 * @param      list   une list_arg_t*.
 * @param      value  en int.
 *
 * @return     la liste mise à jour.
 */
list_arg_t* larg_insert_head(list_arg_t* list, argument_t* value) {
	list_arg_t* new_list = malloc(sizeof(list_arg_t));
	new_list->value = value;
	new_list->next = list;
	return new_list;
}

/**
 * Fonction insérant en queue d'une liste <list> les données <value>.
 *
 * @param      list   une list_arg_t*.
 * @param      value  un pointeur sur un argument.
 *
 * @return     la liste mise à jour.
 */
list_arg_t* larg_insert_tail(list_arg_t* list, argument_t* value) {
	list_arg_t* new_list = malloc(sizeof(list_arg_t));
	new_list->value = value;
	new_list->next = NULL;
	
	if (list == NULL) {
		return new_list;
	}
	
	list_arg_t* temp = list;
	
	while (temp->next != NULL) {
		temp = temp->next;
	}

	temp->next = new_list;
	
	return list;
}

/**
 * Fonction supprimant l'élément en tête de la liste <list>.
 *
 * @param      list  une list_arg_t*.
 *
 * @return     la liste mise à jour.
 */
list_arg_t* larg_remove_head_list(list_arg_t* list) {
	list_arg_t* temp = list;
	
	if (list != NULL) {	
		list = list->next;
		free(temp);
	}
	
	return list;
}

/**
 * Fonction retournant la taille d'une liste en int.
 *
 * @param      list  une list_arg_t*.
 *
 * @return     taille d'une liste en unsigned int.
 */
unsigned int larg_count(list_arg_t* list) {
	list_arg_t* temp = list;
	int size = 0;
	
	if (temp == NULL) {
		return 0;
	}
	
	while (temp != NULL) {
		size++;
		temp = temp->next;
	}
	
	return size;
}

/**
 * Fonction supprimant une liste chainée <list> entière, libère la mémoire.
 *
 * @param      list  une list_arg_t*.
 */
void larg_free_all_list(list_arg_t* list) {
	list_arg_t* temp = list;
	
	while (list != NULL) {
		list = list->next;
		free(temp);
		temp = list;
	}
}
