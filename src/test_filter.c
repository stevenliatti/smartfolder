#include "filter.h"

int main (int argc, char** argv) {
	logger(LOG_DEBUG, stderr, "test du filter\n");

	if (argc > 1) {
		hash_table_t* hash_table = init(CAPACITY, LOAD_FACTOR);
		argument_t arguments[5];
		int hash = -1;
		hash_table = filter(argv[1], arguments, hash_table, &hash);
		free_table(hash_table);
		logger(LOG_DEBUG, stderr, "fin de filter\n");
		return EXIT_SUCCESS;
	}
	else {
		logger(LOG_DEBUG, stderr, "Bad args\n");
		return EXIT_FAILURE;
	}
}
