#include "wrapper.h"
#include "hash_functions.h"

#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

enum state_t { freed, occupied, deleted };

typedef struct string_st {
	char* string;
	enum state_t state;
} string_t;

typedef struct hash_table_st {
	string_t* table;
	int capacity;
	int elements_count;
	double load_factor;
} hash_table_t;

hash_table_t* init(int capacity, double load_factor);
hash_table_t* insert(char* string, hash_table_t* table);
void free_table(hash_table_t* hash_table);
//bool contains(char* string);
//int hash(char* string, int size_of_table);
//void delete(char* string, hash_table_t* table);

#endif
