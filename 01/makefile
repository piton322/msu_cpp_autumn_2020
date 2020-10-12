CFLAGS = -c -Wall -Werror -std=c++17
CC = g++

all: prog

prog: main.o 1.o
	$(CC) main.o 1.o -o prog
1.o: 1.cpp
	$(CC) $(CFLAGS) 1.cpp -o 1.o
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o
clean:
	rm -rf *.prog

	
