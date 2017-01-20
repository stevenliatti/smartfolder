#include "filter.h"

int main (int argc, char** argv) {
	logger(LOG_DEBUG, stderr, "test du filter\n");

	if (argc > 1) {
		int size = 50;
		hash_table_t* hash_table = init(CAPACITY, LOAD_FACTOR);
		int hash = -1;

		// test name_exact_arg
		argument_t arguments[size];
		strcpy(arguments[0].string, "coucou.txt");
		arguments[0].type = name_exact_arg;
		arguments[0].oper = none_op;
		arguments[0].flag = none_flag;

		// test name_contain_arg
		strcpy(arguments[1].string, "coucou");
		arguments[1].type = name_contain_arg;
		arguments[1].oper = none_op;
		arguments[1].flag = none_flag;
		
		// test size_arg egal_op
		strcpy(arguments[2].string, "2656");
		arguments[2].type = size_arg;
		arguments[2].oper = egal_op;
		arguments[2].flag = none_flag;

		// test size_arg more_op
		strcpy(arguments[3].string, "123");
		arguments[3].type = size_arg;
		arguments[3].oper = more_op;
		arguments[3].flag = none_flag;

		// test size_arg less_op
		strcpy(arguments[4].string, "456456");
		arguments[4].type = size_arg;
		arguments[4].oper = less_op;
		arguments[4].flag = none_flag;

		// test owner_arg egal_op user_flag
		strcpy(arguments[11].string, "0");
		arguments[11].type = owner_arg;
		arguments[11].oper = egal_op;
		arguments[11].flag = user_flag;

		// test owner_arg egal_op group_flag
		strcpy(arguments[12].string, "0");
		arguments[12].type = owner_arg;
		arguments[12].oper = egal_op;
		arguments[12].flag = group_flag;

		// test owner_arg not_op user_flag
		strcpy(arguments[13].string, "0");
		arguments[13].type = owner_arg;
		arguments[13].oper = not_op;
		arguments[13].flag = user_flag;

		// test owner_arg not_op group_flag
		strcpy(arguments[14].string, "0");
		arguments[14].type = owner_arg;
		arguments[14].oper = not_op;
		arguments[14].flag = group_flag;

		hash_table = filter(argv[1], arguments, size, hash_table, &hash);
		free_table(hash_table);
		logger(LOG_DEBUG, stderr, "fin de test_filter\n");
		return EXIT_SUCCESS;
	}
	else {
		logger(LOG_DEBUG, stderr, "Bad args\n");
		return EXIT_FAILURE;
	}
}

// enum arg_type_t { name_exact_arg, name_contain_arg, size_arg, date_arg, owner_arg, access_arg, logic_op_arg };
// enum math_op_t { none_op, egal_op, less_op, more_op, not_op };
// enum flags_t { none_flag, date_create_flag, date_modif_flag, date_access_flag, user_flag, group_flag };
