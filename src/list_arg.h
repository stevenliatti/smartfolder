/**
 * @file list_arg.h
 *
 * @brief      Header des fonctions permettant la gestion d'une liste.
 *
 * @author     Steven Liatti et Matthieu Constant
 */

#include "wrapper.h"
#include "logger.h"
#include "argument.h"

#ifndef _LIST_ARG_H_
#define _LIST_ARG_H_

typedef struct list_arg_st {
	argument_t* value;
	struct list_arg_st* next;
} list_arg_t;

/**
 * Fonction retournant une nouvelle liste vide.
 *
 * @return     la nouvelle liste.
 */
list_arg_t* larg_new_list();

/**
 * Fonction retournant true si une liste est vide.
 *
 * @param      list  une list_arg_t*.
 *
 * @return     true si une liste est vide, false sinon.
 */
bool larg_is_empty(const list_arg_t* list);

/**
 * Fonction insérant en tête d'une liste <list> les données <value>.
 *
 * @param      list   une list_arg_t*.
 * @param      value  en int.
 *
 * @return     la liste mise à jour.
 */
list_arg_t* larg_insert_head(list_arg_t* list, argument_t* value);

/**
 * Fonction insérant en queue d'une liste <list> les données <value>.
 *
 * @param      list   une list_arg_t*.
 * @param      value  en int.
 *
 * @return     la liste mise à jour.
 */
list_arg_t* larg_insert_tail(list_arg_t* list, argument_t* value);

/**
 * Fonction supprimant l'élément en tête de la liste <list>.
 *
 * @param      list  une list_arg_t*.
 *
 * @return     la liste mise à jour.
 */
list_arg_t* larg_remove_head_list(list_arg_t* list);

/**
 * Fonction retournant la taille d'une liste en int.
 *
 * @param      list  une list_arg_t*.
 *
 * @return     taille d'une liste en unsigned int.
 */
unsigned int larg_count(list_arg_t* list);

/**
 * Fonction supprimant une liste chainée <list> entière.
 *
 * @param      list  une list_arg_t*.
 * @param      hashName  un hash d'un nom en int.
 * @return     la liste mise à jour.
 */
void larg_free_all_list(list_arg_t* list);

#endif
