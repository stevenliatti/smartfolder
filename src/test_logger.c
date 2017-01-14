#include "wrapper.h"
#include "logger.h"

int main () {
	logger(4, stderr, "%d variable argument\n", 1);
	logger(3, stderr, "%d variable %s\n", 2, "arguments");
	return EXIT_SUCCESS;
}
