#ifndef _WRAPPER_H_
#define _WRAPPER_H_

#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ftw.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>

int _symlink(const char *oldpath, const char *newpath);

#endif