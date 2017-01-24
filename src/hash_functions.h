/**
 * @file hash_functions.h
 * @brief      Header de hash_functions.
 * @author     Steven Liatti et Matthieu Constant
 * @bug        Pas de bugs connus
 * @date       Janvier 2017
 * @version    1.0
 */

#ifndef _HASH_FUNCTIONS_H_
#define _HASH_FUNCTIONS_H_

#include "wrapper.h"
#include "logger.h"

unsigned int closest_prime_number(unsigned int number, bool higher);
unsigned int simple_hash(char* string, unsigned int size_of_table);
unsigned int simple_and_double_hash(unsigned int simple_hash, char* string, unsigned int size_of_table);

#endif
