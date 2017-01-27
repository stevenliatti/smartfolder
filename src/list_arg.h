/**
 * @file list_arg.h
 * @brief      Header des fonctions permettant la gestion d'une liste/pile
 *             d'arguments.
 * @author     Steven Liatti et Matthieu Constant
 * @bug        Pas de bugs connus
 * @date       Janvier 2017
 * @version    1.0
 */

#ifndef _LIST_ARG_H_
#define _LIST_ARG_H_

#include "wrapper.h"
#include "logger.h"
#include "argument.h"

/**
 * @struct list_arg_t list_arg.h
 * @brief      Structure définissant une liste/pile d'arguments.
 */
typedef struct list_arg_st {
	argument_t* value; /*!< La valeur */
	struct list_arg_st* next; /*!< Le prochain élément */
} list_arg_t;

list_arg_t* larg_new_list();
bool larg_is_empty(const list_arg_t* list);
list_arg_t* larg_insert_head(list_arg_t* list, argument_t* value);
list_arg_t* larg_insert_tail(list_arg_t* list, argument_t* value);
list_arg_t* larg_remove_head_list(list_arg_t* list);
unsigned int larg_count(list_arg_t* list);
void larg_free_all_list(list_arg_t* list);

#endif
