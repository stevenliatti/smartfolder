#include "wrapper.h"

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

//bool contains(char* string);
//int hash(char* string, int size_of_table);
void insert(char* string, hash_table_t* table);
//void delete(char* string, hash_table_t* table);

#endif
