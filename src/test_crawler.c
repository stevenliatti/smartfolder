#include "wrapper.h"
#include "logger.h"
#include "crawler.h"

int main (int argc, char** argv) {
	logger(LOG_DEBUG, stderr, "test du crawler\n");

	if (argc > 1) {
		int result = mkdir(argv[1], 0700);
		logger(LOG_DEBUG, stderr, result == EXIT_SUCCESS ? "mkdir success\n" : "mkdir fail\n");
		return crawler(argv[2]);
	}
	return EXIT_FAILURE;
}
