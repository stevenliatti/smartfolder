#include "wrapper.h"
#include "logger.h"
#include "crawler.h"

int main (int argc, char** argv) {
	logger(LOG_DEBUG, stderr, "test du crawler\n");

	if (argc > 1) {
		hash_table_t* files_to_link = init(50, LOAD_FACTOR);
		hash_table_t* paths_traveled = init(CAPACITY, LOAD_FACTOR);

		int result = mkdir(argv[1], 0700);
		logger(LOG_DEBUG, stderr, result == EXIT_SUCCESS ? "mkdir success\n" : "mkdir fail\n");

		crawler(argv[2], paths_traveled, files_to_link);

		logger(LOG_DEBUG, stderr, "crawler terminé\n");

		logger(LOG_DEBUG, stderr, "\nfiles_to_link\n");
		print_table(files_to_link);
		logger(LOG_DEBUG, stderr, "\npaths_traveled\n");
		print_table(paths_traveled);

		free_table(files_to_link);
		free_table(paths_traveled);
		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}
