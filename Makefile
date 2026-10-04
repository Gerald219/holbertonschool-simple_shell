CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=gnu89
SOURCES = $(wildcard *.c)

.PHONY: all test clean
all: hsh

hsh: $(SOURCES) shell.h
	$(CC) $(CFLAGS) $(SOURCES) -o $@

test: hsh
	python3 -m unittest discover -s tests -v

clean:
	rm -f hsh
