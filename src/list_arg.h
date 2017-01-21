/**
* @file list_arg.h
*
* Header des fonctions permettant la gestion d'une liste.
*
* @author Steven Liatti
*/

#include "wrapper.h"
#include "logger.h"
#include "argument.h"

#ifndef _LIST_H_
#define _LIST_H_

typedef struct list_st {
	argument_t* value;
	struct list_st* next;
} list_t;

/**
* Fonction retournant une nouvelle liste vide.
* 
* @param void
* @return la nouvelle liste.
*/
list_t* larg_new_list();

/**
* Fonction retournant true si une liste est vide.
* 
* @param list une list_t*.
* @return true si une liste est vide, false sinon.
*/
bool larg_is_empty(const list_t* list);

/**
* Fonction insérant en tête d'une liste <list> les données <value>.
* 
* @param list une list_t*.
* @param value en int.
* @return la liste mise à jour.
*/
list_t* larg_insert_head(list_t* list, argument_t* value);

/**
* Fonction insérant en queue d'une liste <list> les données <value>.
* 
* @param list une list_t*.
* @param value en int.
* @return la liste mise à jour.
*/
list_t* larg_insert_tail(list_t* list, argument_t* value);

/**
* Fonction supprimant l'élément en tête de la liste <list>.
* 
* @param list une list_t*.
* @return la liste mise à jour.
*/
list_t* larg_remove_head_list(list_t* list);

/**
* Fonction supprimant l'élément en tête de la liste <list> et place
* la value dans <value>.
* 
* @param list une list_t*.
* @param value un pointeur sur un boolean.
* @return la liste mise à jour.
*/
list_t* larg_remove_head_list_arg(list_t* list, argument_t* value);

/**
* Fonction retournant la taille d'une liste en int.
* 
* @param list une list_t*.
* @return taille d'une liste en unsigned int.
*/
unsigned int larg_count(list_t* list);

/**
* Fonction supprimant une liste chainée <list> entière.
* 
* @param list une list_t*.
* @param hashName un hash d'un nom en int.
* @return la liste mise à jour.
*/
void larg_free_all_list(list_t* list);

#endif
