#include "wrapper.h"
#include "logger.h"
#include "crawler.h"

int main (int argc, char** argv) {
	logger(LOG_DEBUG, stderr, "test du crawler\n");

	if (argc > 1) {
		int result = mkdir(argv[1], 0700);
		if (result == 0)
			logger(LOG_DEBUG, stderr, "mkdir success\n");
		else
			logger(LOG_DEBUG, stderr, "mkdir fail\n");

		result = nftw(argv[2], crawler, 15, 0);
		if (result == 0)
			logger(LOG_DEBUG, stderr, "nftw success\n");
		else
			logger(LOG_DEBUG, stderr, "nftw fail\n");

		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
