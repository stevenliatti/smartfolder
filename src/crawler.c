#include "crawler.h"

int crawler(const char *filepath, const struct stat *info,
			const int typeflag, struct FTW *pathinfo) {
    const char *const filename = filepath + pathinfo->base;

    printf("filename : %s\n", filename);

    if (typeflag == FTW_SLN)
        printf(" %s (dangling symlink)\n", filepath);
    else if (typeflag == FTW_F)
        printf(" %s [FICHIER]\n", filepath);
    else if (typeflag == FTW_D || typeflag == FTW_DP)
        printf(" %s [DOSSIER]\n", filepath);
    else if (typeflag == FTW_DNR)
        printf(" %s/ (unreadable)\n", filepath);
    else
        printf(" %s (unknown)\n", filepath);

    return EXIT_SUCCESS;
}
