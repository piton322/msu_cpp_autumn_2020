CFLAGS = -c -Wall -Werror -std=c++17
CC = g++

all: prog

test:
	./prog

prog: tests.o bigint.o arr.o
	$(CC) tests.o bigint.o -o prog

bigint.o: bigint.cpp
	$(CC) $(CFLAGS) bigint.cpp -o bigint.o

tests.o: tests.cpp
	$(CC) $(CFLAGS) tests.cpp -o tests.o

clean:
	rm -rf *.prog
