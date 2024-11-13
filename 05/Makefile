CC=g++
FLAGS=-std=c++20 -Wall -Wextra -Werror -pedantic
GTEST_FLAGS=-lgtest -lgtest_main -lpthread

all: main tests

main: main.o
	$(CC) $(FLAGS) main.o -o main

main.o: main.cpp serializer.hpp serializer.tpp
	$(CC) $(FLAGS) main.cpp -c

tests: tests.cpp
	$(CC) $(FLAGS) tests.cpp -o tests $(GTEST_FLAGS)

test:
	./tests

clean:
	rm -f main tests *.o
