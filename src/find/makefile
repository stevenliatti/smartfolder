CC = gcc
FLAGS = -g -Wall -std=gnu99
SRCS=$(wildcard *.c)
OUT=$(SRCS:%.c=%)

all: $(OUT)

%: %.c
	$(CC) $(FLAGS) $< -o $@

clean:
	rm -rf $(OUT)

rebuild: clean all
