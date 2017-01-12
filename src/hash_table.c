#include "hash_table.h"

bool is_prime(int number) {
	// Tester de 2 jusqu'à la racine carrée de number.
	int limit = ((int) sqrt(number)) + 1;
	bool is_prime = true;
	
	if (number == 0 || number == 1)
		return false;

	if (number == 2)
		return true;
	
	for (int i = 2; i <= limit; i++) {
		if (number % i == 0)
			is_prime = false;
	}
	return is_prime;
}

int closest_prime_number(int number, bool higher) {
	int i = number;
	if (higher) {
		do {
			i++;
		} while (!is_prime(i));
	}
	else {
		do {
			i--;
		} while (!is_prime(i) && i > 1);
	}
	return i;
}

int simple_hash(char* string, int size_of_table) {
	int hash = 0;
	for(int i = 0; i < (int) strlen(string); i++)
		hash = hash + string[i];
	return hash % size_of_table;
}

int double_hash(char* string, int size_of_table) {
	return 1 + (simple_hash(string, size_of_table) % closest_prime_number(size_of_table, false));
}

int simple_and_double_hash(int simple_hash, char* string, int size_of_table) {
	return (simple_hash + double_hash(string, size_of_table)) % size_of_table;
}

bool contains(char* string, hash_table_t* hash_table) {
	int hash = simple_hash(string, hash_table->capacity);

	do {
		if (strcmp(hash_table->table[hash].string, string) == 0 && hash_table->table[hash].state == occupied)
			return true;

		hash = simple_and_double_hash(hash, string, hash_table->capacity);
	} while(hash_table->table[hash].state != freed);
	
	return false;

	//return strcmp(hash_table->table[0].string, string) == 0 && hash_table->table[0].state != occupied;
}

void insert(char* string, hash_table_t* hash_table) {

}

void delete(char* string, hash_table_t* hash_table) {

}
