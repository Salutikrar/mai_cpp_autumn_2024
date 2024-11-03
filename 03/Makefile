CC=g++
FLAGS=-std=c++20 -Wall -Wextra -Werror -pedantic
GTEST_FLAGS=-lgtest -lgtest_main -lpthread

all: main tests

main: main.o matrix.o
	$(CC) $(FLAGS) main.o matrix.o -o main

main.o: main.cpp matrix.hpp
	$(CC) $(FLAGS) main.cpp -c

matrix.o: matrix.cpp matrix.hpp
	$(CC) $(FLAGS) matrix.cpp -c

tests: matrix.o tests.cpp
	$(CC) $(FLAGS) matrix.o tests.cpp -o tests $(GTEST_FLAGS)

test:
	./tests

clean:
	rm -f main tests *.o
