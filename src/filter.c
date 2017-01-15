#include "filter.h"

hash_table_t* filter(char* string, hash_table_t* hash_table, int* hash) {
	logger(LOG_DEBUG, stderr, "???????????????? In filter, string, hash : %s, %d\n", string, *hash);
	bool inserted;
	return insert_with_hash(string, hash_table, &inserted, hash);
}
