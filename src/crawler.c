#include "crawler.h"
#include "argument.h"

bool is_dir(struct dirent* entry) {
	return entry->d_type == DT_DIR || entry->d_type == DT_LNK;
}

void crawler(char* path, char* folder_path, hash_table_t* paths_traveled, hash_table_t* files_to_link, argument_t* arguments, int args_size) {
	DIR* dir = _opendir(path);
	if (dir == NULL) return;
	struct dirent* entry = NULL;
	bool inserted;
	int hash;
	char entry_path[PATH_MAX], resolved_path[PATH_MAX];
	while ((entry = readdir(dir)) != NULL) {
		if (!(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)) {
			strcpy(entry_path, path);
			logger(LOG_DEBUG_DONE, stderr, "entry_path (1) : %s\n", entry_path);
			strcat(entry_path, "/");
			logger(LOG_DEBUG_DONE, stderr, "entry_path (2) : %s\n", entry_path);
			strcat(entry_path, entry->d_name);
			logger(LOG_DEBUG_DONE, stderr, "entry_path (3) : %s\n", entry_path);
			realpath(entry_path, resolved_path);
			logger(LOG_DEBUG_DONE, stderr, "\nd_name : %s\n", entry->d_name);
			logger(LOG_DEBUG_DONE, stderr, "resolved_path : %s\n", resolved_path);

			if (is_dir(entry)) {
				logger(LOG_DEBUG_DONE, stderr, "is_dir : %s\n", resolved_path);
				paths_traveled = insert(resolved_path, paths_traveled, &inserted);
				if (inserted) {
					crawler(entry_path, folder_path, paths_traveled, files_to_link, arguments, args_size);
				}
			}
			else {
				logger(LOG_DEBUG_DONE, stderr, "NOT is_dir : %s\n", resolved_path);
				if (!contains(resolved_path, files_to_link, &hash)) {
					logger(LOG_DEBUG_DONE, stderr, "hash : %d\n", hash);
					//files_to_link = insert_with_hash(resolved_path, files_to_link, &inserted, &hash);
					// call the FILTER
					files_to_link = filter(resolved_path, folder_path, arguments, args_size, files_to_link, &hash);
				}
			}
		}
	}
	_closedir(dir);
}
