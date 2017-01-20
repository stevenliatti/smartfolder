#include "filter.h"

void log_stat(char* path, struct stat* buf) {
	logger(LOG_DEBUG, stderr, "Information for %s\n", path);
	logger(LOG_DEBUG, stderr, "---------------------------\n");
	logger(LOG_DEBUG, stderr, "File Size: \t\t%d bytes\n",buf->st_size);
	logger(LOG_DEBUG, stderr, "Number of Links: \t%d\n",buf->st_nlink);
	logger(LOG_DEBUG, stderr, "File inode: \t\t%d\n",buf->st_ino);

	logger(LOG_DEBUG, stderr, "File Permissions: \t");
	logger(LOG_DEBUG, stderr, (S_ISDIR(buf->st_mode)) ? "d" : "-");
	logger(LOG_DEBUG, stderr, (buf->st_mode & S_IRUSR) ? "r" : "-");
	logger(LOG_DEBUG, stderr, (buf->st_mode & S_IWUSR) ? "w" : "-");
	logger(LOG_DEBUG, stderr, (buf->st_mode & S_IXUSR) ? "x" : "-");
	logger(LOG_DEBUG, stderr, (buf->st_mode & S_IRGRP) ? "r" : "-");
	logger(LOG_DEBUG, stderr, (buf->st_mode & S_IWGRP) ? "w" : "-");
	logger(LOG_DEBUG, stderr, (buf->st_mode & S_IXGRP) ? "x" : "-");
	logger(LOG_DEBUG, stderr, (buf->st_mode & S_IROTH) ? "r" : "-");
	logger(LOG_DEBUG, stderr, (buf->st_mode & S_IWOTH) ? "w" : "-");
	logger(LOG_DEBUG, stderr, (buf->st_mode & S_IXOTH) ? "x" : "-");
	logger(LOG_DEBUG, stderr, "\n\n");

	logger(LOG_DEBUG, stderr, "The file %s a symbolic link\n", (S_ISLNK(buf->st_mode)) ? "is" : "is not");
}

bool eval_exact_name(char* path, char* expression) {
	const char slash = '/';
	logger(LOG_DEBUG, stderr, "path, in eval_exact_name : %s\n", path);
	char copy_path[255];
	strcpy(copy_path, path);
	logger(LOG_DEBUG, stderr, "copy_path : %s\n", copy_path);
	char* filename = strrchr(copy_path, slash); // ici on récupère le nom du fichier avec le slash, ex : /test.txt
	strncpy(filename, filename + 1, strlen(filename) - 0); // ici on retire le slash de filename, ex : test.txt
	filename[strlen(filename)] = '\0'; // on met à NULL le dernier caractère de filename
	logger(LOG_DEBUG, stderr, "in eval_exact_name, filename : %s\n", filename);
	logger(LOG_DEBUG, stderr, "expression : %s\n", expression);
	return strcmp(filename, expression) == 0;
}

bool eval_contain_name(char* path, char* expression) {
	const char slash = '/';
	logger(LOG_DEBUG, stderr, "path, in eval_contain_name : %s\n", path);
	char copy_path[255];
	strcpy(copy_path, path);
	logger(LOG_DEBUG, stderr, "copy_path : %s\n", copy_path);
	char* filename = strrchr(copy_path, slash); // ici on récupère le nom du fichier avec le slash, ex : /test.txt
	strncpy(filename, filename + 1, strlen(filename) - 0); // ici on retire le slash de filename, ex : test.txt
	filename[strlen(filename)] = '\0'; // on met à NULL le dernier caractère de filename
	logger(LOG_DEBUG, stderr, "in eval_contain_name, filename : %s\n", filename);
	logger(LOG_DEBUG, stderr, "expression : %s\n", expression);
	return strcasestr(filename, expression) != NULL || strcasestr(expression, filename) != NULL;
}

bool eval_size(char* path, argument_t* argument, struct stat* buf) {
	logger(LOG_DEBUG, stderr, "path, in eval_size : %s\n", path);
	logger(LOG_DEBUG, stderr, "argument string, type, oper, flag : %s, %d, %d, %d\n", argument->string, argument->type, argument->oper, argument->flag);
	
	if(stat(path, buf) < 0)
		return false;

	long size_criteria = atol(argument->string);
	logger(LOG_DEBUG, stderr, "size_criteria = %ld\n", size_criteria);
	long size_path = (long) buf->st_size;
	logger(LOG_DEBUG, stderr, "size_path = %ld\n", size_path);

	switch(argument->oper) {
		case egal_op:
			logger(LOG_DEBUG, stderr, "in switch, egal_op\n");
			return size_path == size_criteria;
		case less_op:
			logger(LOG_DEBUG, stderr, "in switch, less_op\n");
			return size_path < size_criteria;
		case more_op:
			logger(LOG_DEBUG, stderr, "in switch, more_op\n");
			return size_path > size_criteria;	
		default:
			logger(LOG_DEBUG, stderr, "in switch, default\n");
			return false;
	}
}

bool eval_owner(char* path, argument_t* argument, struct stat* buf) {
	logger(LOG_DEBUG, stderr, "path, in eval_owner : %s\n", path);
	logger(LOG_DEBUG, stderr, "argument string, type, oper, flag : %s, %d, %d, %d\n", argument->string, argument->type, argument->oper, argument->flag);
	
	if(stat(path, buf) < 0)
		return false;
	
	int id_criteria = atoi(argument->string);
	logger(LOG_DEBUG, stderr, "id_criteria = %d\n", id_criteria);
	int uid_path = buf->st_uid;
	logger(LOG_DEBUG, stderr, "uid_path = %d\n", uid_path);
	int gid_path = buf->st_gid;
	logger(LOG_DEBUG, stderr, "gid_path = %d\n", gid_path);

	switch(argument->oper) {
		case egal_op:
			logger(LOG_DEBUG, stderr, "in switch, egal_op\n");
			switch(argument->flag) {
				case user_flag:
					logger(LOG_DEBUG, stderr, "in switch, user_flag\n");
					return id_criteria == uid_path;
				case group_flag:
					logger(LOG_DEBUG, stderr, "in switch, group_flag\n");
					return id_criteria == gid_path;
				default:
					logger(LOG_DEBUG, stderr, "in switch, default\n");
					return false;
			}
		case not_op:
			logger(LOG_DEBUG, stderr, "in switch, not_op\n");
			switch(argument->flag) {
				case user_flag:
					logger(LOG_DEBUG, stderr, "in switch, user_flag\n");
					return id_criteria != uid_path;
				case group_flag:
					logger(LOG_DEBUG, stderr, "in switch, group_flag\n");
					return id_criteria != gid_path;
				default:
					logger(LOG_DEBUG, stderr, "in switch, default\n");
					return false;
			}
		default:
			logger(LOG_DEBUG, stderr, "in switch, default\n");
			return false;
	}
}

bool eval(char* path, argument_t* arguments, int args_size) {
	struct stat buf;
	if(stat(path, &buf) < 0)
		return false;
	//log_stat(path, &buf);
	logger(LOG_DEBUG, stderr, "in eval, before test, args_size : %d\n", args_size);
	bool test = eval_owner(path, &arguments[14], &buf);
	logger(LOG_DEBUG, stderr, "eval_owner : %s\n", test ? "true" : "false");

	return test;
}

hash_table_t* filter(char* path, argument_t* arguments, int args_size, hash_table_t* hash_table, int* hash) {
	logger(LOG_DEBUG, stderr, "???????????????? In filter, path, hash : %s, %d\n", path, *hash);
	bool inserted;
	
	if (eval(path, arguments, args_size)) {
		logger(LOG_DEBUG, stderr, "+++++ file %s GARDÉ DANS LA TABLE +++++\n", path);
		// appeler le linker ici
		return insert_with_hash(path, hash_table, &inserted, hash);
	}
	logger(LOG_DEBUG, stderr, "Fin de filter\n");
	return hash_table;
}
