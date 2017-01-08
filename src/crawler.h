#include "wrapper.h"

#ifndef _CRAWLER_H_
#define _CRAWLER_H_

#ifndef USE_FDS
#define USE_FDS 15
#endif

int crawler(const char *filepath, const struct stat *info,
            const int typeflag, struct FTW *pathinfo);

#endif
