CFLAGS = -c -Wall -Werror -std=c++17
CC = g++

all: prog

test:
	./prog

prog: tests.o error.o
	$(CC) tests.o error.o -o prog

error.o: error.cpp
	$(CC) $(CFLAGS) error.cpp -o error.o

tests.o: tests.cpp
	$(CC) $(CFLAGS) tests.cpp -o tests.o

clean:
	rm -rf *.prog
