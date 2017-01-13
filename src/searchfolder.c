#include "wrapper.h"
#include "crawler.h"
#include "parser.h"

int main(int argc, char** argv) {
	parse_arg(argc,argv);
/*
	if (argc > 1) {
		int result = mkdir(argv[1], 0700);
		if (result == 0) {
			printf("mkdir success\n");
		}
		else {
			printf("mkdir fail\n");
		}

		result = nftw(argv[2], crawler, USE_FDS, 0);
		if (result == 0) {
			printf("nftw success\n");
		}
		else {
			printf("nftw fail\n");
		}

		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE; */
}
