#include "logger.h"

#define LOG_LEVEL 3

void logger(int log_level, FILE *stream, char *format, ...) {
	va_list arguments;
	va_start(arguments, format);

	if (log_level <= LOG_LEVEL)
		vfprintf(stream, format, arguments);
	
	va_end(arguments);
}