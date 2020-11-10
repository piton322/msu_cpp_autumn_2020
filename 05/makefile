CFLAGS = -c -Wall -Werror -std=c++17
CC = g++

all: prog

test:
	./prog

prog: tests.o serializer.o deserializer.o error.o
	$(CC) tests.o serializer.o deserializer.o error.o -o prog

serializer.o: serializer.cpp
	$(CC) $(CFLAGS) serializer.cpp -o serializer.o

deserializer.o: deserializer.cpp
	$(CC) $(CFLAGS) deserializer.cpp -o deserializer.o

error.o: error.cpp
	$(CC) $(CFLAGS) error.cpp -o error.o

tests.o: tests.cpp
	$(CC) $(CFLAGS) tests.cpp -o tests.o

clean:
	rm -rf *.prog
