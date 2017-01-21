/**
* @file list_bool.c
*
* Implémentation des fonctions permettant la gestion d'une liste.
*
* @author Steven Liatti
*/

#include "list_bool.h"

list_t* new_list() {
	return NULL;
}

bool is_empty(const list_t* list) {
	return list == NULL;
}

list_t* insert_head(list_t* list, bool value) {
	list_t* new_list = malloc(sizeof(list_t));
	new_list->value = value;
	new_list->next = list;
	return new_list;
}

list_t* insert_tail(list_t* list, bool value) {
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

list_t* search(list_t* list, bool value) {
	if (list == NULL) {
		return list;
	}
	else {
		list_t* temp = list;
		
		while (temp != NULL) {
			if (temp->value == value) {
				return temp;
			}
			temp = temp->next;
		}
		
		return temp;
	}
}

list_t* remove_list(list_t* list, bool value) {
	list_t* temp = list;
	
	// Si l'élément contenant value se trouve en tête de liste. 
	if (list != NULL) {
		if (list->value == value) {
			list = list->next;
			free(temp);
			return list;
		}
		// Sinon on le cherche plus loin dans la liste chainée.
		else {
			while (temp->next != NULL) {
				if (temp->next->value == value) {
					list_t* anotherTemp = temp->next;
					temp->next = temp->next->next;
					free(anotherTemp);
					return list;
				}
				else {
					temp = temp->next;
				}
			}
			
			return list;
		}
	}
	
	return list;
}

list_t* remove_head_list(list_t* list) {
	list_t* temp = list;
	
	if (list != NULL) {	
		list = list->next;
		free(temp);
	}
	
	return list;
}

list_t* remove_head_list_bool(list_t* list, bool* value) {
	list_t* temp = list;
	
	if (list != NULL) {
		*value = list->value;		
		list = list->next;
		free(temp);
	}
	
	return list;
}

unsigned int count(list_t* list) {
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

void free_all_list(list_t* list) {
	list_t* temp = list;
	
	while (list != NULL) {
		list = list->next;
		free(temp);
		temp = list;
	}
}

bool print_list(bool value) {
	logger(LOG_DEBUG, stderr, "%d ", value);
	return value;
}

void apply(list_t* list, bool(*oper)(bool n)) {
	list_t* temp = list;
	
	while (temp != NULL) {
		temp->value = oper(temp->value);
		temp = temp->next;
	}
	logger(LOG_DEBUG, stderr, "\n");
}
