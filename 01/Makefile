CC=g++
FLAGS=-std=c++20 -Wall -Wextra -Werror -pedantic
GTEST_FLAGS=-lgtest -lgtest_main -lpthread

all: main tests.o

main: main.o allocator.o
	$(CC) $(FLAGS) main.o allocator.o -o main

main.o: main.cpp allocator.hpp
	$(CC) $(FLAGS) main.cpp -c

allocator.o: allocator.cpp allocator.hpp
	$(CC) $(FLAGS) allocator.cpp -c

tests.o: allocator.o tests.cpp
	$(CC) $(FLAGS) allocator.o tests.cpp -o tests $(GTEST_FLAGS)

test:
	./tests

clean:
	rm -f main tests *.o
