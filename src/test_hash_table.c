#include "wrapper.h"
#include "hash_table.h"

int main () {
	hash_table_t* hash_table = init(10, 0.5);

	char str[] = "lun mar mer jeu ven sam dim lun mar";
	const char s[] = " ";
	char *token;
	bool inserted;
	
	/* get the first token */
	token = strtok(str, s);

	/* walk through other tokens */
	while(token != NULL) {
		logger(LOG_DEBUG, stderr, "---------------------------------------------- tentative pour : %s\n", token);
		hash_table = insert(token, hash_table, &inserted);
		logger(LOG_DEBUG, stderr, "element inserted : %s\n", inserted ? "true" : "false");
		token = strtok(NULL, s);
	}

	logger(LOG_DEBUG, stderr, "_______________________________ affichage de la hash_table\n");
	print_table(hash_table);
	free_table(hash_table);

	return EXIT_SUCCESS;
}
