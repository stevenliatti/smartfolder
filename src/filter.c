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

bool eval_file(char* path, argument_t* arguments) {
	struct stat buf;
	if(stat(path, &buf) < 0)    
		return false;
	log_stat(path, &buf);
	
	return true;
}

hash_table_t* filter(char* path, argument_t* arguments, hash_table_t* hash_table, int* hash) {
	logger(LOG_DEBUG, stderr, "???????????????? In filter, path, hash : %s, %d\n", path, *hash);
	bool inserted;
	
	if (eval_file(path, arguments)) {
		logger(LOG_DEBUG, stderr, "+++++ file %s gardé\n", path);
		return insert_with_hash(path, hash_table, &inserted, hash);
	}
	logger(LOG_DEBUG, stderr, "Fin de filter\n");
	return hash_table;
}
