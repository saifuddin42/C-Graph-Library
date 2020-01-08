all: test

CFLAGS=-g -Og -Wall -std=c99
CC=gcc

test: test.c graph.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f test
