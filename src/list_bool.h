/**
 * @file list_bool.h
 * @brief      Header des fonctions permettant la gestion d'une liste/pile de
 *             boolean.
 * @author     Steven Liatti et Matthieu Constant
 * @bug        Pas de bugs connus
 * @date       Janvier 2017
 * @version    1.0
 */

#ifndef _LIST_BOOL_H_
#define _LIST_BOOL_H_

#include "wrapper.h"
#include "logger.h"
#include "argument.h"

/**
 * @struct list_bool_t list_bool.h
 * @brief      Structure définissant une liste/pile de boolean.
 */
typedef struct list_bool_st {
	bool value; /*!< La valeur */
	struct list_bool_st* next; /*!< Le prochain élément */
} list_bool_t;

list_bool_t* new_list();
bool is_empty(const list_bool_t* list);
list_bool_t* insert_head(list_bool_t* list, bool value);
list_bool_t* insert_tail(list_bool_t* list, bool value);
list_bool_t* remove_head_list(list_bool_t* list);
list_bool_t* remove_head_list_bool(list_bool_t* list, bool* value);
unsigned int count(list_bool_t* list);
void free_all_list(list_bool_t* list);

#endif
