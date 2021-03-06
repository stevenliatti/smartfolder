/**
 * @file filter.h
 * @brief      Header du Filter.
 * @author     Steven Liatti et Matthieu Constant
 * @bug        Pas de bugs connus
 * @date       Janvier 2017
 * @version    1.0
 */

#ifndef _FILTER_H_
#define _FILTER_H_

#include "wrapper.h"
#include "logger.h"
#include "hash_table.h"
#include "argument.h"
#include "list_bool.h"
#include "linker.h"

hash_table_t* filter(char* path, char* folder_path, argument_t* arguments, int args_size, hash_table_t* hash_table, int* hash);

#endif
