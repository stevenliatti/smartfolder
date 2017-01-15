#include "crawler.h"

#ifndef FILE_DESCRIPTORS
#define FILE_DESCRIPTORS 15
#endif

int walkthrough(const char* path, const struct stat* info, const int typeflag, struct FTW* pathinfo) {
	logger(LOG_DEBUG, stderr, "%-3s %2d %7jd   %-40s %d %s\n",
		(typeflag == FTW_D) ?   "d"   : (typeflag == FTW_DNR) ? "dnr" :
		(typeflag == FTW_DP) ?  "dp"  : (typeflag == FTW_F) ?   "f" :
		(typeflag == FTW_NS) ?  "ns"  : (typeflag == FTW_SL) ?  "sl" :
		(typeflag == FTW_SLN) ? "sln" : "???",
		pathinfo->level, info->st_size,
		path, pathinfo->base, path + pathinfo->base);

	return EXIT_SUCCESS;
}

int crawler(const char* path) {
	int result = nftw(path, walkthrough, FILE_DESCRIPTORS, 0);
	logger(LOG_DEBUG, stderr, result == EXIT_SUCCESS ? "nftw success\n" : "nftw fail\n");
	return result;
}
