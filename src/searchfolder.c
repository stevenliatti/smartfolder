/**
 * @file searchfolder.c
 * @brief      Main
 * @author     Steven Liatti et Matthieu Constant
 * @bug        Pas de bugs connus
 * @date       Janvier 2017
 * @version    1.0
 */

#include "wrapper.h"
#include "logger.h"
#include "crawler.h"
#include "filter.h"
#include "parser.h"

int main(int argc, char** argv) {
	if (argc > 1) {
		hash_table_t* files_to_link  = init(CAPACITY, LOAD_FACTOR);
		hash_table_t* paths_traveled = init(CAPACITY, LOAD_FACTOR);
		int args_size = 0;

		// Faut faire une copie profonde de argv
		char** new_argv = malloc((argc + 1) * sizeof(*new_argv));
		for(int i = 0; i < argc; i++) {
			size_t length = strlen(argv[i]) + 1;
			new_argv[i] = malloc(length);
			memcpy(new_argv[i], argv[i], length);
		}
		new_argv[argc] = NULL;

		argument_t* arguments = parse_arg(argc, new_argv, &args_size);
		
		int result = mkdir(argv[1], 0777);
		logger(LOG_DEBUG, stderr, "mkdir %s\n", result == 0 ? "success" : "fail");
		
		crawler(argv[2], argv[1], paths_traveled, files_to_link, arguments, args_size);

		logger(LOG_DEBUG, stderr, "%lu\n", sizeof arguments);

		free_table(files_to_link);
		free_table(paths_traveled);
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
