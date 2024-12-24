#include<iostream>
#include<functional>
#include <cstdint>
#include <limits>
#include "token.hpp"

int main()
{
    TokenParser parser;
    parser.SetStartCallback([](){std::cout << "Start!\n";});
    parser.SetEndCallback([](){std::cout << "End!\n";});
    parser.SetDigitTokenCallback([](const uint64_t a){std::cout << "Digit: " << a << "\n";});
    parser.SetStringTokenCallback([](const std::string& a){std::cout << "String: " << a << "\n";});
    std::string line;
    while (std::getline(std::cin, line))
    {
        parser.Parse(line);
    }
}
