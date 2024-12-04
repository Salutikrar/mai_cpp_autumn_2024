#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "format.hpp"

int main() {
	std::pair<int, int> a;
	auto text1 = format("{1}+{3} = {0}-{2}", 10, 1, 6, 3);
	std::cout << text1 << '\n';
}
