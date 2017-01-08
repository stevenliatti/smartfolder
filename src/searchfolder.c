#include "wrapper.h"

int main(int argc, char** argv) {
	if (argc > 1) {
		int result = mkdir(argv[1], atoi(argv[2]));
		if (result == 0) {
			printf("success\n");
		}
		else {
			printf("fail\n");
		}
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}