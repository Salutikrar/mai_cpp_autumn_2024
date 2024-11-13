#include <iostream>
#include "bigint.hpp"

// import BigInt;
// import std.core;

int main()
{
    BigInt a("99999999");
    std::cout << a << "\n";
    BigInt b("99999999");
    std::cout << b << "\n";
    BigInt c("-234567892345678923456789");
    std::cout << c << "\n";
    BigInt d("-111111111111111111111111");
    std::cout << d << "\n";
    BigInt e("123456781234567812345678");
    std::cout << e << "\n";
    BigInt f("111111111111111111111111");
    std::cout << f << "\n";
    std::cout << (a - b) << "\n";
    std::cout << (c - d) << "\n";
    std::cout << (e - f) << "\n";
    std::cout << (a * b) << "\n";
    std::cout << (a == b) << "\n";
    std::cout << (a != b) << "\n";
    std::cout << c + d << "\n";



}
