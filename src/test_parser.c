#include "wrapper.h"
#include "logger.h"
#include "crawler.h"
#include "filter.h"
#include "parser.h"

int main (int argc, char** argv) {
	logger(LOG_DEBUG, stderr, "Test du parser\n");

	int args_size = 0;
	argument_t* arguments = parse_arg(argc, argv, &args_size);

	free(arguments);

	return EXIT_SUCCESS;
}
