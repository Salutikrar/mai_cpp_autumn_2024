CC=g++
FLAGS=-std=c++20 -Wall -Wextra -Werror -pedantic
GTEST_FLAGS=-lgtest -lgtest_main -lpthread

all: main tests

main: main.cpp format.hpp format.tpp
	$(CC) $(FLAGS) main.cpp -o main

tests: tests.cpp format.hpp format.tpp
	$(CC) $(FLAGS) tests.cpp -o tests $(GTEST_FLAGS)

test:
	./tests

clean:
	rm -f main tests *.o

