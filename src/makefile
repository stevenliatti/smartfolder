CC = gcc
FLAGS = -g -Wall -Wextra -std=gnu99
SRCS=$(wildcard *.c)
OBJECTS=$(SRCS:%.c=%.o)

all: searchfolder

searchfolder: $(OBJECTS)
	$(CC) $(FLAGS) $^ -o $@

searchfolder.o: searchfolder.c
	$(CC) $(FLAGS) $< -c

crawler.o: crawler.c
	$(CC) $(FLAGS) $< -c

hash_table.o: hash_table.c
	$(CC) $(FLAGS) $< -c

linker.o: linker.c
	$(CC) $(FLAGS) $< -c

wrapper.o: wrapper.c
	$(CC) $(FLAGS) $< -c

clean:
	rm -rf *.o searchfolder

rebuild: clean all
