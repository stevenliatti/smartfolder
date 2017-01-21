#include "wrapper.h"
#include "logger.h"
#include "hash_table.h"
#include "argument.h"
#include "list_bool.h"

#ifndef _FILTER_H_
#define _FILTER_H_

hash_table_t* filter(char* path, argument_t* arguments, int args_size, hash_table_t* hash_table, int* hash);

#endif
