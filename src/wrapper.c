#include "wrapper.h"

int inline _symlink(const char *oldpath, const char *newpath) {
	return symlink(oldpath, newpath);
}
