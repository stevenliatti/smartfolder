#include "wrapper.h"

#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

typedef struct hash_table_st {
	char** table;
	int capacity;
	int elements_count;
	double load_factor;
} hash_table_t;

int hash(char* string);
bool contains(char* string);
void insert(char* string, hash_table_t table);
void delete(char* string, hash_table_t table);

#endif
