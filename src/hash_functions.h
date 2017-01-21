/**
 * @file hash_functions.h
 * @brief      Header de hash_functions.
 * @author     Steven Liatti
 * @bug        Pas de bugs connus
 * @date       Janvier 2017
 * @version    1.0
 */

#include "wrapper.h"
#include "logger.h"

#ifndef _HASH_FUNCTIONS_H_
#define _HASH_FUNCTIONS_H_

unsigned int closest_prime_number(unsigned int number, bool higher);
unsigned int simple_hash(char* string, unsigned int size_of_table);
unsigned int simple_and_double_hash(unsigned int simple_hash, char* string, unsigned int size_of_table);

#endif
