/**
 * @file argument.h
 * @brief      Ce fichier contient les énumérations et la structure pour la
 *             gestion des arguments du programme. Cette structure est partagée
 *             par le Parser et par le Filter.
 * @author     Steven Liatti et Matthieu Constant
 * @bug        Pas de bugs connus
 * @date       Janvier 2017
 * @version    1.0
 */

#include "wrapper.h"
#include "logger.h"
#include "hash_table.h"

#ifndef _ARGUMENT_H_
#define _ARGUMENT_H_

/**
 * @brief      Énumération des différents critères de recherche possibles.
 */
enum arg_type_t {
	name_exact_arg, /*!< Par nom exact */
	name_contain_arg, /*!< Par nom contenu */
	size_arg, /*!< Par taille de fichier */
	date_arg, /*!< Par date */
	owner_arg, /*!< Par propriétaire */
	perm_arg, /*!< Par permissions */
	and_op_arg, /*!< Par opérateur logique ET */
	or_op_arg, /*!< Par opérateur logique OU */
	not_op_arg /*!< Par opérateur logique INVERSE */
};

/**
 * @brief      Énumération des différents opérateurs mathématiques associés aux
 *             critères.
 */
enum math_op_t {
	none_op, /*!< Pas d'opérateur */
	egal_op, /*!< Égalité */
	less_op, /*!< Plus petit que */
	more_op, /*!< Plus grand que */
	not_op /*!< Inverse (pour le propriétaire par exemple) */
};

/**
 * @brief      Énumération des différents indicateurs associés aux critères.
 */
enum flags_t {
	none_flag, /*!< Aucun */
	date_create_flag, /*!< Date de création */
	date_modif_flag, /*!< Date de modification */
	date_access_flag, /*!< Date de d'accès */
	user_flag, /*!< Utilisateur */
	group_flag /*!< Groupe */
};

/**
 * @struct argument_t argument.h
 * @brief      Cette structure modélise un critère donné en argument du
 *             programme.
 */
typedef struct {
	char string[255]; /*!< La valeur brute, à convertir dans le Filter */
	enum arg_type_t type; /*!< Le type d'argument */
	enum math_op_t oper; /*!< L'opérateur mathématique */
	enum flags_t flag; /*!< L'indicateur (optionnel) */
} argument_t;

#endif
