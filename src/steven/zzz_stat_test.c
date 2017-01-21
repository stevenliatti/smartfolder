#include "wrapper.h"

int main(int argc, char** argv) {
	struct stat buf;
	if(stat(argv[1], &buf) < 0)
		return 1;

	printf("%d ", S_IRUSR);
	printf("%d ", S_IWUSR);
	printf("%d ", S_IXUSR);
	printf("%d ", S_IRGRP);
	printf("%d ", S_IWGRP);
	printf("%d ", S_IXGRP);
	printf("%d ", S_IROTH);
	printf("%d ", S_IWOTH);
	printf("%d ", S_IXOTH);
	
	printf("\n");
	
	printf("%d ", S_IRWXU);
	printf("%d ", S_IRWXG);
	printf("%d ", S_IRWXO);

	printf("\n");

	return EXIT_SUCCESS;
}