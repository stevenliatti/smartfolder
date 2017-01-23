/**
 * @file list_arg.c
 *
 * @brief      Implémentation des fonctions permettant la gestion d'une liste.
 *
 * @author     Steven Liatti et Matthieu Constant
 */

#include "list_arg.h"

list_arg_t* larg_new_list() {
	return NULL;
}

bool larg_is_empty(const list_arg_t* list) {
	return list == NULL;
}

list_arg_t* larg_insert_head(list_arg_t* list, argument_t* value) {
	list_arg_t* new_list = malloc(sizeof(list_arg_t));
	new_list->value = value;
	new_list->next = list;
	return new_list;
}

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

list_arg_t* larg_remove_head_list(list_arg_t* list) {
	list_arg_t* temp = list;
	
	if (list != NULL) {	
		list = list->next;
		free(temp);
	}
	
	return list;
}

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

void larg_free_all_list(list_arg_t* list) {
	list_arg_t* temp = list;
	
	while (list != NULL) {
		list = list->next;
		free(temp);
		temp = list;
	}
}
