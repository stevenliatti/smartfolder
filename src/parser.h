/**
 * @file parser.h
 * @brief      Header du parser.
 * @author     Steven Liatti et Matthieu Constant
 * @bug        Pas de bugs connus
 * @date       Janvier 2017
 * @version    1.0
 */

#ifndef _PARSER_H_
#define _PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <regex.h>

#include "wrapper.h"
#include "logger.h"
#include "argument.h"
#include "list_arg.h"

bool regex_match(char* request, char* regex);
argument_t* parse_arg(int argc, char** argv, int* args_size);

#endif
