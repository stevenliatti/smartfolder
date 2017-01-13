#include "wrapper.h"

#ifndef _HASH_FUNCTIONS_H_
#define _HASH_FUNCTIONS_H_

int simple_hash(char* string, int size_of_table);
int simple_and_double_hash(int simple_hash, char* string, int size_of_table);

#endif
