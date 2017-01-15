#include "wrapper.h"

int _symlink(const char* oldpath, const char* newpath) {
	return symlink(oldpath, newpath);
}

DIR* _opendir(const char* path) {
	return opendir(path);
}

int _closedir(DIR* dir) {
	return closedir(dir);
}