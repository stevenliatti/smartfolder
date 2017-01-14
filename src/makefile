CC = gcc
FLAGS = -g -Wall -Wextra -std=gnu99
TESTS = test_hash_table
EXEC = searchfolder $(TESTS)

# Fabrique tous les executables (tests inclus)
all: $(EXEC)

# Programme principal
searchfolder: searchfolder.o parser.o crawler.o hash_table.o hash_functions.o linker.o wrapper.o
	$(CC) $(FLAGS) $^ -o $@ -lm

searchfolder.o: searchfolder.c
	$(CC) $(FLAGS) $< -c

# Librairies
parser.o: parser.c
	$(CC) $(FLAGS) $< -c

crawler.o: crawler.c
	$(CC) $(FLAGS) $< -c

hash_table.o: hash_table.c
	$(CC) $(FLAGS) $< -c

hash_functions.o: hash_functions.c
	$(CC) $(FLAGS) $< -c

linker.o: linker.c
	$(CC) $(FLAGS) $< -c

wrapper.o: wrapper.c
	$(CC) $(FLAGS) $< -c

# Tests
all_test: $(TESTS)

test_hash_table: test_hash_table.o hash_table.o hash_functions.o wrapper.o
	$(CC) $(FLAGS) $^ -o $@ -lm

test_hash_table.o: test_hash_table.c
	$(CC) $(FLAGS) $< -c

# Ménage
clean:
	rm -rf *.o $(EXEC)

rebuild: clean all
