/**
 * @file linker.h
 * @brief      Header du linker.
 * @author     Steven Liatti et Matthieu Constant
 * @bug        Pas de bugs connus
 * @date       Janvier 2017
 * @version    1.0
 */

#ifndef _LINKER_H_
#define _LINKER_H_

#include "wrapper.h"
#include "logger.h"

int linker(const char* file_linked, const char* link_path);

#endif