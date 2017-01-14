#include "wrapper.h"
#include "logger.h"

#ifndef _CRAWLER_H_
#define _CRAWLER_H_

int walkthrough(const char *filepath, const struct stat *info, const int typeflag, struct FTW *pathinfo);

#endif
