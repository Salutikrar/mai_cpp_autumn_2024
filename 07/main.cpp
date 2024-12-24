#include <iostream>
#include "avl.hpp"

int main(){
	Avl<int, int> m;
	for(int i = 0 ; i < 10 ; i++){
		m[i] = i;
	}
	for(int i = 10 ; i < 20 ; i++){
		std::pair<int, int> a = {i, i};
		m.insert(a);
	}
	for(int i = 0; i < 20; ++i){
		if(!m.contains(i)){
			std::cout << "it's very bad\n";
		}
	}
	auto it1 = m.begin();
	for(auto it = m.begin(); it != m.end(); ++it){
		std::cout << (*it).first << ' ' << (*it).second << '\n';
		it1 = it;
	}
	std::cout << '\n';
	for(auto it = it1; it != m.begin(); --it){
		std::cout << (*it).first << ' ' << (*it).second << '\n';
	}
	std::cout << '\n';
	for(auto it = m.rbegin(); it != m.rend(); ++it){
		std::cout << (*it).first << ' ' << (*it).second << '\n';
		it1 = it;
	}
	std::cout << '\n';
	for(auto it = it1; it != m.rbegin(); --it){
		std::cout << (*it).first << ' ' << (*it).second << '\n';
		it1 = it;
	}
	std::cout << m.size() << '\n';
	for(int i = 0 ; i < 20 ; i++){
//		m.print();
//		std::cout << "-------------------------------------------------------1\n";
		m.erase(i);
//		m.print();
//		std::cout << "-------------------------------------------------------2\n";
		m[i] = i;
	}
	std::cout << m.size() << '\n';
	m.clear();
	std::cout << m.empty() << '\n';

}
