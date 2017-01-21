#include "wrapper.h"
#include "logger.h"
#include "crawler.h"
#include "filter.h"
#include "parser.h"

int main(int argc, char** argv) {
	if (argc > 1) {
		hash_table_t* files_to_link  = init(CAPACITY, LOAD_FACTOR);
		hash_table_t* paths_traveled = init(CAPACITY, LOAD_FACTOR);
		argument_t* arguments;
		int args_size = 0;

		//	PLACER LE PARSER ICI

		int result = mkdir(argv[1], 0777);
		logger(LOG_DEBUG, stderr, "mkdir %s\n", result == 0 ? "success" : "fail");
		
		crawler(argv[2], paths_traveled, files_to_link, arguments, args_size);

		free_table(files_to_link);
		free_table(paths_traveled);
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
