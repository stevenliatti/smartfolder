/**
 * @file wrapper.h
 * @brief      Header du wrapper pour les appels systèmes utilisés.
 * @author     Steven Liatti et Matthieu Constant
 * @bug        Pas de bugs connus
 * @date       Janvier 2017
 * @version    1.0
 */

#ifndef _WRAPPER_H_
#define _WRAPPER_H_

#define _XOPEN_SOURCE 700
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <errno.h>
#include <stdarg.h>
#include <limits.h>
#include <getopt.h>
#include <regex.h>

int _symlink(const char* oldpath, const char* newpath);
pid_t _fork();
int _access(const char* name, int mode);
int _kill(pid_t pid, int sig);

#endif
