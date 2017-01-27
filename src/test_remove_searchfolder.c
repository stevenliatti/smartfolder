#include "wrapper.h"
#include "logger.h"
#include "crawler.h"

int remove_searchfolder(const char* path) {
	DIR* dir = opendir(path);
	struct dirent* entry = NULL;

	if (dir == NULL) return EXIT_FAILURE;

	while ((entry = readdir(dir)) != NULL) {
		if (!(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0)) {
			char entry_path[PATH_MAX];
			strcpy(entry_path, path);
			strcat(entry_path, "/");
			strcat(entry_path, entry->d_name);
			_unlink(entry_path);
		}
	}
	closedir(dir);

	if (_rmdir(path) < 0) {
		logger(LOG_ERROR, stderr, "failed to remove folder %s\n", path);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int main(int argc, char** argv) {
	if (argc == 2) {
		logger(LOG_DEBUG, stderr, "Call remove_searchfolder\n");
		remove_searchfolder(argv[1]);
	}
	return EXIT_SUCCESS;
}
