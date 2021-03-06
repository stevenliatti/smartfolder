CC = gcc
FLAGS = -g -Wall -Wextra -std=gnu99 -D_BSD_SOURCE
TESTS = test_hash_table test_logger test_crawler test_filter test_linker test_parser test_remove_searchfolder
EXEC = searchfolder

# Fabrique tous les executables (tests inclus)
all: $(EXEC)

# Programme principal
searchfolder: searchfolder.o parser.o crawler.o list_bool.o list_arg.o hash_table.o hash_functions.o filter.o linker.o logger.o wrapper.o
	$(CC) $(FLAGS) $^ -o $@ -lm

searchfolder.o: searchfolder.c
	$(CC) $(FLAGS) $< -c

# Librairies
parser.o: parser.c
	$(CC) $(FLAGS) $< -c

crawler.o: crawler.c
	$(CC) $(FLAGS) $< -c

list_bool.o: list_bool.c
	$(CC) $(FLAGS) $< -c

list_arg.o: list_arg.c
	$(CC) $(FLAGS) $< -c

hash_table.o: hash_table.c
	$(CC) $(FLAGS) $< -c

hash_functions.o: hash_functions.c
	$(CC) $(FLAGS) $< -c

filter.o: filter.c
	$(CC) $(FLAGS) $< -c

linker.o: linker.c
	$(CC) $(FLAGS) $< -c

logger.o: logger.c
	$(CC) $(FLAGS) $< -c

wrapper.o: wrapper.c
	$(CC) $(FLAGS) $< -c

# Tests
all_test: $(TESTS)

test_hash_table: test_hash_table.o hash_table.o hash_functions.o logger.o wrapper.o
	$(CC) $(FLAGS) $^ -o $@ -lm

test_logger: test_logger.o logger.o wrapper.o
	$(CC) $(FLAGS) $^ -o $@

test_crawler: test_crawler.o crawler.o list_bool.o filter.o hash_table.o hash_functions.o linker.o logger.o wrapper.o
	$(CC) $(FLAGS) $^ -o $@ -lm

test_filter: test_filter.o filter.o list_bool.o hash_table.o hash_functions.o linker.o logger.o wrapper.o
	$(CC) $(FLAGS) $^ -o $@ -lm

test_linker: test_linker.o linker.o logger.o wrapper.o
	$(CC) $(FLAGS) $^ -o $@

test_parser: test_parser.o list_arg.o parser.o linker.o logger.o wrapper.o
	$(CC) $(FLAGS) $^ -o $@

test_remove_searchfolder: test_remove_searchfolder.o logger.o wrapper.o
	$(CC) $(FLAGS) $^ -o $@

test_hash_table.o: test_hash_table.c
	$(CC) $(FLAGS) $< -c

test_logger.o: test_logger.c
	$(CC) $(FLAGS) $< -c

test_crawler.o: test_crawler.c
	$(CC) $(FLAGS) $< -c

test_filter.o: test_filter.c
	$(CC) $(FLAGS) $< -c

test_linker.o: test_linker.c
	$(CC) $(FLAGS) $< -c

test_parser.o: test_parser.c
	$(CC) $(FLAGS) $< -c

test_remove_searchfolder.o: test_remove_searchfolder.c
	$(CC) $(FLAGS) $< -c

# Ménage
clean:
	rm -rf *.o $(EXEC) $(TESTS)

rebuild: clean all
