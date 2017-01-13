#include "hash_table.h"
#include "hash_functions.h"

// bool contains(char* string, hash_table_t* hash_table) {
// 	int hash = simple_hash(string, hash_table->capacity);

// 	do {
// 		if (strcmp(hash_table->table[hash].string, string) == 0 && hash_table->table[hash].state == occupied)
// 			return true;

// 		hash = simple_and_double_hash(hash, string, hash_table->capacity);
// 	} while(hash_table->table[hash].state != freed);
	
// 	return false;

// 	//return strcmp(hash_table->table[0].string, string) == 0 && hash_table->table[0].state != occupied;
// }

void insert(char* string, hash_table_t* hash_table) {
	int hash = simple_hash(string, hash_table->capacity);

	do {
		if (strcmp(hash_table->table[hash].string, string) == 0 && hash_table->table[hash].state == occupied)
			hash = simple_and_double_hash(hash, string, hash_table->capacity);
	} while(hash_table->table[hash].state != freed);
	
	hash_table->table[hash].string = malloc(sizeof(char) * (strlen(string) + 1));
	strcpy(hash_table->table[hash].string, string);
	hash_table->table[hash].state = occupied;
}

// void delete(char* string, hash_table_t* hash_table) {

// }
