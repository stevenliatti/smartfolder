#include "wrapper.h"
#include "logger.h"
#include "hash_table.h"

#ifndef _ARGUMENT_H_
#define _ARGUMENT_H_

enum arg_type_t { name_arg, size_arg, date_arg, owner_arg, access_arg, logic_op_arg };
enum math_op_t { egal_op, less_op, more_op, not_op };
enum flags_t { date_create_flag, date_modif_flag, date_access_flag, user_flag, group_flag };

typedef struct argument_st {
	char* string;
	enum arg_type_t type;
	enum math_op_t oper;
	enum flags_t flag;
} argument_t;

#endif