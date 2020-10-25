CFLAGS = -c -Wall -Werror -std=c++17
CC = g++

all: prog

test:
	./prog

prog: third_tests.o matrix.o arr.o
	$(CC) third_tests.o matrix.o arr.o -o prog

arr.o: arr.cpp
	$(CC) $(CFLAGS) arr.cpp -o arr.o

matrix.o: matrix.cpp
	$(CC) $(CFLAGS) matrix.cpp -o matrix.o

third_tests.o: third_tests.cpp
	$(CC) $(CFLAGS) third_tests.cpp -o third_tests.o

clean:
	rm -rf *.prog

	
