/**
 * @file crawler.h
 * @brief      Header du Crawler.
 * @author     Steven Liatti et Matthieu Constant
 * @bug        Pas de bugs connus
 * @date       Janvier 2017
 * @version    1.0
 */

#ifndef _CRAWLER_H_
#define _CRAWLER_H_

#include "wrapper.h"
#include "logger.h"
#include "hash_table.h"
#include "filter.h"

bool is_dir(struct dirent* entry);
void crawler(char* path, char* folder_path, hash_table_t* paths_traveled, 
	hash_table_t* files_to_link, argument_t* arguments, int args_size);
#endif
