#include "hash_functions.h"

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
	printf("is_prime return : (%d) %d\n", number, is_prime);
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
	printf("closest_prime_number return : %d\n", i);
	return i;
}

int simple_hash(char* string, int size_of_table) {
	int hash = 0;
	for(int i = 0; i < (int) strlen(string); i++)
		hash = hash + string[i];

	printf("simple_hash return : %d, %d\n", hash, hash % size_of_table);
	return hash % size_of_table;
}

int double_hash(char* string, int size_of_table) {
	int i = 1 + (simple_hash(string, size_of_table) % closest_prime_number(size_of_table, false));
	printf("double_hash return : %d\n", i);
	return i;
}

int simple_and_double_hash(int simple_hash, char* string, int size_of_table) {
	int i = (simple_hash + double_hash(string, size_of_table)) % size_of_table;
	printf("simple_and_double_hash return : %d\n", i);
	return i;
}