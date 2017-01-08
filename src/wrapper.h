#ifndef _WRAPPER_H_
#define _WRAPPER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <string.h>
#include <stdbool.h>
#include <assert.h>

int _symlink(const char *oldpath, const char *newpath);

#endif