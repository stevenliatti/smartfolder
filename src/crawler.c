#include "crawler.h"

bool is_dir(struct dirent* entry) {
	return entry->d_type == DT_DIR || entry->d_type == DT_LNK;
}

void crawler(char* path, hash_table_t* paths_traveled, hash_table_t* files_to_link) {
	bool inserted;
	DIR* dir = _opendir(path);
	struct dirent* entry = NULL;
	if (dir == NULL) return;

	while ((entry = readdir(dir)) != NULL) {
		if (!(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)) {
			strcpy(entry_path, path);
			logger(LOG_ALL, stderr, "entry_path (1) : %s\n", entry_path);
			strcat(entry_path, "/");
			logger(LOG_ALL, stderr, "entry_path (2) : %s\n", entry_path);
			strcat(entry_path, entry->d_name);
			logger(LOG_ALL, stderr, "entry_path (3) : %s\n", entry_path);
			realpath(entry_path, resolved_path);
			logger(LOG_DEBUG, stderr, "\nd_name : %s\n", entry->d_name);
			logger(LOG_DEBUG, stderr, "resolved_path : %s\n", resolved_path);

			if (is_dir(entry)) {
				logger(LOG_DEBUG, stderr, "is_dir : %s\n", resolved_path);
				paths_traveled = insert(resolved_path, paths_traveled, &inserted);
				if (inserted) {
					crawler(entry_path, paths_traveled, files_to_link);
				}
			}
			else {
				logger(LOG_DEBUG, stderr, "NOT is_dir : %s\n", resolved_path);
				files_to_link = insert(resolved_path, files_to_link, &inserted);
			}
		}
	}
	_closedir(dir);
}
