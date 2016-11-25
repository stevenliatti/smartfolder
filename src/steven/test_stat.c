#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char** argv) {
	struct stat buffer;
	stat("a.txt", &buffer);

	printf("%d\n", buffer.st_uid);
	printf("%d\n", buffer.st_gid);
	printf("%o\n", buffer.st_mode & 07777);
	printf("%d\n", buffer.st_size);
	printf("%d\n", buffer.st_atime);
	printf("%d\n", buffer.st_mtime);
	printf("%d\n", buffer.st_ctime);

	return EXIT_SUCCESS;
}
