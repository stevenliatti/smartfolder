#include "linker.h"

int linker(const char* file_linked, const char* link_name) {
	char resolved_file_linked[PATH_MAX], resolved_link_name[PATH_MAX];
	realpath(file_linked, resolved_file_linked);
	realpath(link_name, resolved_link_name);
	logger(LOG_DEBUG, stderr, "in linker, resolved_file_linked, resolved_link_name : \n");
	logger(LOG_DEBUG, stderr, "%s,\t%s\n", resolved_file_linked, resolved_link_name);
	int res = _symlink(resolved_file_linked, resolved_link_name);

	while (res != 0) {
		srand(time(NULL));
		int i = rand() % 10000;
		char str[5];
		sprintf(str, "%d", i);
		char copy_link_name[PATH_MAX];
		strcpy(copy_link_name, link_name);
		logger(LOG_DEBUG, stderr, "copy_link_name : %s\n", copy_link_name);
		strcat(copy_link_name, str);
		realpath(copy_link_name, resolved_link_name);
		logger(LOG_DEBUG, stderr, "new resolved_link_name : %s\n", resolved_link_name);
		res = _symlink(resolved_file_linked, resolved_link_name);
	}

	return res;
}
