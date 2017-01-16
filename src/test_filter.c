#include "filter.h"

int main (int argc, char** argv) {
	logger(LOG_DEBUG, stderr, "test du filter\n");

	if (argc > 1) {
		int size = 2;
		hash_table_t* hash_table = init(CAPACITY, LOAD_FACTOR);
		argument_t arguments[size];
		strcpy(arguments[0].string, "coucou.txt");
		arguments[0].type = name_arg;
		arguments[0].oper = none_op;
		arguments[0].flag = none_flag;
		int hash = -1;

		hash_table = filter(argv[1], arguments, size, hash_table, &hash);
		free_table(hash_table);
		logger(LOG_DEBUG, stderr, "fin de filter\n");
		return EXIT_SUCCESS;
	}
	else {
		logger(LOG_DEBUG, stderr, "Bad args\n");
		return EXIT_FAILURE;
	}
}
