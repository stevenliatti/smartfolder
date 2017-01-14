#include "hash_table.h"

hash_table_t* init(int capacity, double load_factor) {
	int real_capacity = closest_prime_number(capacity, true);
	hash_table_t* hash_table = malloc(sizeof(hash_table_t));
	hash_table->table = malloc(sizeof(string_t) * real_capacity);
	hash_table->capacity = real_capacity;
	hash_table->elements_count = 0;
	hash_table->load_factor = load_factor;
	for (int i = 0; i < real_capacity; i++) {
		hash_table->table[i].state = freed;
	}
	return hash_table;
}

hash_table_t* resize(hash_table_t* hash_table) {
	logger(LOG_DEBUG, stderr, "::::::::::::::::::: in resize\n");
	hash_table_t* new_hash_table = init(2 * hash_table->capacity, hash_table->load_factor);
	for (int i = 0; i < hash_table->capacity; i++) {
		if (hash_table->table[i].state != freed) {
			insert(hash_table->table[i].string, new_hash_table);
		}
	}
	free_table(hash_table);
	logger(LOG_DEBUG, stderr, "::::::::::::::::::: resize success\n");
	return new_hash_table;
}

hash_table_t* insert(char* string, hash_table_t* hash_table) {
	if ((double) hash_table->elements_count / (double) hash_table->capacity > hash_table->load_factor) {
		hash_table = resize(hash_table);
	}
	logger(LOG_DEBUG, stderr, "//////////////////////// in insert, capacity : %d\n", hash_table->capacity);
	int hash = simple_hash(string, hash_table->capacity);

	while(hash_table->table[hash].state != freed) {
		if (strcmp(hash_table->table[hash].string, string) == 0 && hash_table->table[hash].state == occupied) {
			logger(LOG_DEBUG, stderr, "NOT insert %s\n", string);
			return hash_table;
		}
		hash = simple_and_double_hash(hash, string, hash_table->capacity);
	}
	hash_table->table[hash].string = malloc(sizeof(char) * (strlen(string) + 1));
	strcpy(hash_table->table[hash].string, string);
	hash_table->table[hash].state = occupied;
	hash_table->elements_count++;
	logger(LOG_DEBUG, stderr, "insert %s\n", string);
	return hash_table;
}

void free_table(hash_table_t* hash_table) {
	for (int i = 0; i < hash_table->capacity; i++) {
		free(hash_table->table[i].string);
	}
	free(hash_table->table);
	free(hash_table);
}
