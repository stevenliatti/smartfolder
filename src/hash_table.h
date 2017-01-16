#include "wrapper.h"
#include "hash_functions.h"

#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#define CAPACITY 10
#define LOAD_FACTOR 0.75
#define GROWTH_FACTOR 2.0

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
bool contains(char* string, hash_table_t* hash_table, int* hash);
hash_table_t* insert_with_hash(char* string, hash_table_t* hash_table, bool* inserted, int* hash);
hash_table_t* insert(char* string, hash_table_t* hash_table, bool* inserted);
void free_table(hash_table_t* hash_table);
void print_table(hash_table_t* hash_table);

#endif