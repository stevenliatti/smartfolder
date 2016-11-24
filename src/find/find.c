#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

void find_by_name(struct dirent* entity, struct stat* buffer) {
	stat(entity->d_name, buffer);

	if (S_ISDIR(buffer->st_mode) == 0) {
		/* pourquoi dans le dossier . ça marche, mais pas dans le dossier parent (..) ou un sous-dossier ? */
		printf("%s - %d\n", entity->d_name, S_ISREG(buffer->st_mode));
	}
}

int main(int argc, char** argv) {
	if (argc > 1) {
		DIR* dir;
		struct dirent *entity;
		dir = opendir(argv[1]);
		struct stat buffer;

		if (dir) {
			while ((entity = readdir(dir)) != NULL) {
				find_by_name(entity, &buffer);
			}

			closedir(dir);
		}
		else {
			printf("Mauvais directory\n");
		}

		return EXIT_SUCCESS;
	}
	else {
		printf("find [directory] [options]\n");
	}
}
