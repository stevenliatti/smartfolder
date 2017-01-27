/**
 * @file logger.h
 * @brief      Header du logger.
 * @author     Steven Liatti et Matthieu Constant
 * @bug        Pas de bugs connus
 * @date       Janvier 2017
 * @version    1.0
 */

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "wrapper.h"

#define LOG_ERROR 0
#define LOG_WARNING 1
#define LOG_DEBUG 2

void logger(int log_level, FILE *stream, char *format, ...);

#endif
