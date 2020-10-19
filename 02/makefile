CFLAGS = -c -Wall -Werror -std=c++17
CC = g++

all: prog

test:
	./prog

prog: second_tests.o parser.o
	$(CC) second_tests.o parser.o -o prog

parser.o: parser.cpp
	$(CC) $(CFLAGS) parser.cpp -o parser.o

second_tests.o: second_tests.cpp
	$(CC) $(CFLAGS) second_tests.cpp -o second_tests.o

clean:
	rm -rf *.prog

	
