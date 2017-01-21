#include "wrapper.h"
#include "logger.h"
#include "hash_table.h"
#include "argument.h"
#include "list_bool.h"
#include "linker.h"

int main(int argc, char** argv) {
	if (argc > 2) {
		logger(LOG_DEBUG, stderr, "file linked, name link : %s, %s\n", argv[1], argv[2]);
		int res = linker(argv[1], argv[2]);
		logger(LOG_DEBUG, stderr, "res : %d\n", res);
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
