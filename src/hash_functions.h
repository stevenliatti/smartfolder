#include "wrapper.h"
#include "logger.h"

#ifndef _HASH_FUNCTIONS_H_
#define _HASH_FUNCTIONS_H_

bool is_prime(int number);
int closest_prime_number(int number, bool higher);
int simple_hash(char* string, int size_of_table);
int double_hash(char* string, int size_of_table);
int simple_and_double_hash(int simple_hash, char* string, int size_of_table);

#endif
