#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char** argv) {
	int res = symlink(argv[1], argv[2]);
	printf("res %d\n", res);
	return EXIT_SUCCESS;
}
