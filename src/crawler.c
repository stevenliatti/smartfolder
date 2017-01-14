#include "crawler.h"

#ifndef FILE_DESCRIPTORS
#define FILE_DESCRIPTORS 15
#endif

int walkthrough(const char *filepath, const struct stat *info, const int typeflag, struct FTW *pathinfo) {
    const char *const filename = filepath + pathinfo->base;

    logger(LOG_DEBUG, stderr, "filename : %s\n", filename);
    logger(LOG_DEBUG, stderr, "info : %d\n", info->st_mode);

    if (typeflag == FTW_SLN)
        logger(LOG_DEBUG, stderr, " %s (dangling symlink)\n", filepath);
    else if (typeflag == FTW_F)
        logger(LOG_DEBUG, stderr, " %s [FICHIER]\n", filepath);
    else if (typeflag == FTW_D || typeflag == FTW_DP)
        logger(LOG_DEBUG, stderr, " %s [DOSSIER]\n", filepath);
    else if (typeflag == FTW_DNR)
        logger(LOG_DEBUG, stderr, " %s/ (unreadable)\n", filepath);
    else
        logger(LOG_DEBUG, stderr, " %s (unknown)\n", filepath);

    return EXIT_SUCCESS;
}

int crawler(const char* path, ) {
    return nftw(path, walkthrough, FILE_DESCRIPTORS, 0)
}