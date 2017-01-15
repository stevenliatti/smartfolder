#include "wrapper.h"

#ifndef _LOGGER_H_
#define _LOGGER_H_

#define LOG_ERROR 0
#define LOG_WARNING 1
#define LOG_INFO 2
#define LOG_DEBUG 3
#define LOG_ALL 4

void logger(int log_level, FILE *stream, char *format, ...);

#endif