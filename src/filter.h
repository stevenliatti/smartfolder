#include "wrapper.h"
#include "logger.h"
#include "hash_table.h"

#ifndef _FILTER_H_
#define _FILTER_H_

hash_table_t* filter(char* string, hash_table_t* hash_table, int* hash);

#endif
