#include "wrapper.h"
#include "logger.h"
#include "hash_table.h"
#include "filter.h"

#ifndef _CRAWLER_H_
#define _CRAWLER_H_

void crawler(char* path, hash_table_t* paths_traveled, hash_table_t* files_to_link, argument_t* arguments, int args_size);

#endif
