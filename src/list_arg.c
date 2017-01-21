/**
* @file list_arg.c
*
* Implémentation des fonctions permettant la gestion d'une liste.
*
* @author Steven Liatti
*/

#include "list_arg.h"

list_t* larg_new_list() {
	return NULL;
}

bool larg_is_empty(const list_t* list) {
	return list == NULL;
}

list_t* larg_insert_head(list_t* list, argument_t* value) {
	list_t* new_list = malloc(sizeof(list_t));
	new_list->value = value;
	new_list->next = list;
	return new_list;
}

list_t* larg_insert_tail(list_t* list, argument_t* value) {
	list_t* new_list = malloc(sizeof(list_t));
	new_list->value = value;
	new_list->next = NULL;
	
	if (list == NULL) {
		return new_list;
	}
	
	list_t* temp = list;
	
	while (temp->next != NULL) {
		temp = temp->next;
	}

	temp->next = new_list;
	
	return list;
}

list_t* larg_remove_head_list(list_t* list) {
	list_t* temp = list;
	
	if (list != NULL) {	
		list = list->next;
		free(temp);
	}
	
	return list;
}

list_t* larg_remove_head_list_arg(list_t* list, argument_t* value) {
	list_t* temp = list;	

	if (list != NULL) {
		value = list->value;		
		list = list->next;
		free(temp);
	}
	
	return list;
}

unsigned int larg_count(list_t* list) {
	list_t* temp = list;
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

void larg_free_all_list(list_t* list) {
	list_t* temp = list;
	
	while (list != NULL) {
		list = list->next;
		free(temp);
		temp = list;
	}
}
