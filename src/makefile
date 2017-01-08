CC = gcc
FLAGS = -g -Wall -Wextra -std=gnu99
SRCS=$(wildcard *.c)
OUT=$(SRCS:%.c=%.o)

all: searchfolder

searchfolder: $(OUT)
	$(CC) $(FLAGS) $^ -o $@

searchfolder.o: searchfolder.c
	$(CC) $(FLAGS) $< -c

linker.o: linker.c
	$(CC) $(FLAGS) $< -c

wrapper.o: wrapper.c
	$(CC) $(FLAGS) $< -c

clean:
	rm -rf *.o searchfolder

rebuild: clean all
