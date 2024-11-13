CC=g++
FLAGS=-std=c++20 -Wall -Wextra -Werror -pedantic
GTEST_FLAGS=-lgtest -lgtest_main -lpthread

all: main tests

main: main.o bigint.o
	$(CC) $(FLAGS) main.o bigint.o -o main

main.o: main.cpp bigint.hpp
	$(CC) $(FLAGS) main.cpp -c

bigint.o: bigint.cpp bigint.hpp
	$(CC) $(FLAGS) bigint.cpp -c

tests: bigint.o tests.cpp
	$(CC) $(FLAGS) bigint.o tests.cpp -o tests $(GTEST_FLAGS)

test:
	./tests

clean:
	rm -f main tests *.o
