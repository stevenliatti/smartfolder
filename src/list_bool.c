/**
 * @file list_bool.c
 * @brief      Implémentation des fonctions permettant la gestion d'une
 *             liste/pile de boolean.
 * @author     Steven Liatti
 * @bug        Pas de bugs connus
 * @date       Janvier 2017
 * @version    1.0
 */

#include "list_bool.h"

/**
 * @brief      Fonction retournant une nouvelle liste vide.
 *
 * @return     la nouvelle liste.
 */
list_bool_t* new_list() {
	return NULL;
}

/**
 * @brief      Fonction retournant true si une liste est vide.
 *
 * @param      list  une list_bool_t*.
 *
 * @return     true si une liste est vide, false sinon.
 */
bool is_empty(const list_bool_t* list) {
	return list == NULL;
}

/**
 * @brief      Fonction insérant en tête d'une liste <list> les données <value>.
 *
 * @param      list   une list_bool_t*.
 * @param      value  en boolean.
 *
 * @return     la liste mise à jour.
 */
list_bool_t* insert_head(list_bool_t* list, bool value) {
	list_bool_t* new_list = malloc(sizeof(list_bool_t));
	new_list->value = value;
	new_list->next = list;
	return new_list;
}


/**
 * @brief      Fonction insérant en queue d'une liste <list> les données
 *             <value>.
 *
 * @param      list   une list_bool_t*.
 * @param      value  en boolean.
 *
 * @return     la liste mise à jour.
 */
list_bool_t* insert_tail(list_bool_t* list, bool value) {
	list_bool_t* new_list = malloc(sizeof(list_bool_t));
	new_list->value = value;
	new_list->next = NULL;
	
	if (list == NULL) {
		return new_list;
	}
	
	list_bool_t* temp = list;
	
	while (temp->next != NULL) {
		temp = temp->next;
	}

	temp->next = new_list;
	
	return list;
}

/**
 * @brief      Fonction supprimant l'élément en tête de la liste <list>.
 *
 * @param      list  une list_bool_t*.
 *
 * @return     la liste mise à jour.
 */
list_bool_t* remove_head_list(list_bool_t* list) {
	list_bool_t* temp = list;
	
	if (list != NULL) {	
		list = list->next;
		free(temp);
	}
	
	return list;
}


/**
 * @brief      Fonction supprimant l'élément en tête de la liste <list> et place
 *             la value dans <value>.
 *
 * @param      list   une list_bool_t*.
 * @param      value  un pointeur sur un boolean.
 *
 * @return     la liste mise à jour.
 */
list_bool_t* remove_head_list_bool(list_bool_t* list, bool* value) {
	list_bool_t* temp = list;
	
	if (list != NULL) {
		*value = list->value;		
		list = list->next;
		free(temp);
	}
	
	return list;
}

/**
 * @brief      Fonction retournant la taille d'une liste en int.
 *
 * @param      list  une list_bool_t*.
 *
 * @return     taille d'une liste en unsigned int.
 */
unsigned int count(list_bool_t* list) {
	list_bool_t* temp = list;
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
 * @brief      Fonction supprimant une liste chainée <list> entière.
 *
 * @param      list  une list_bool_t*.
 * @return     la liste mise à jour.
 */
void free_all_list(list_bool_t* list) {
	list_bool_t* temp = list;
	
	while (list != NULL) {
		list = list->next;
		free(temp);
		temp = list;
	}
}
