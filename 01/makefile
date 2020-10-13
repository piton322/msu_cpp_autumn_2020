CFLAGS = -c -Wall -Werror -std=c++17
CC = g++

all: prog

test:
	./prog

prog: main.o allocator.o
	$(CC) main.o allocator.o -o prog

allocator.o: allocator.cpp
	$(CC) $(CFLAGS) allocator.cpp -o allocator.o

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o

clean:
	rm -rf *.prog

	
