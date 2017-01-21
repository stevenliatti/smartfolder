/**
 * @file list_bool.h
 * @brief      Header des fonctions permettant la gestion d'une liste/pile de boolean.
 * @author     Steven Liatti
 * @bug        Pas de bugs connus
 * @date       Janvier 2017
 * @version    1.0
 */

#include "wrapper.h"
#include "logger.h"
#include "argument.h"

#ifndef _LIST_H_
#define _LIST_H_

/**
 * @struct list_t list_bool.h
 * @brief      Structure définissant une liste/pile.
 */
typedef struct list_st {
	bool value; /*!< La valeur */
	struct list_st* next; /*!< Le prochain élément */
} list_t;

list_t* new_list();
bool is_empty(const list_t* list);
list_t* insert_head(list_t* list, bool value);
list_t* insert_tail(list_t* list, bool value);
list_t* remove_head_list(list_t* list);
list_t* remove_head_list_bool(list_t* list, bool* value);
unsigned int count(list_t* list);
void free_all_list(list_t* list);

#endif
