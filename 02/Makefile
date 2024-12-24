CC=g++
FLAGS=-std=c++20 -Wall -Wextra -Werror -pedantic
GTEST_FLAGS=-lgtest -lgtest_main -lpthread

all: libtests.a tests main

main: main.o libtoken.a
	$(CC) $(FLAGS) main.o -L. -ltoken -o main

main.o: main.cpp token.hpp
	$(CC) $(FLAGS) main.cpp -c

libtests.a: token.o
	ar rc libtoken.a token.o

token.o: token.cpp token.hpp
	$(CC) $(FLAGS) token.cpp -c

tests: libtoken.a tests.cpp
	$(CC) $(FLAGS) tests.cpp -L. -ltoken -o tests $(GTEST_FLAGS)

test:
	./tests

clean:
	rm -f main tests *.o
