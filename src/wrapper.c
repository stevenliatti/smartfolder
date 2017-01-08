#include "wrapper.h"

int _symlink(const char *oldpath, const char *newpath) {
	return symlink(oldpath, newpath);
}
