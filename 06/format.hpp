#include <iostream>
#include <string>
#include <vector>
#include <sstream>

enum class Error {
	WrongContent,
	EmptyNum,
	WrongNum,
	WrongOpenBracket,
	WrongArg
};

size_t string_to_int(const std::string & s){
	size_t cur = 0;
	int n = s.size();
	for(int i = 0 ; i < n; ++i){
		cur = cur * 10 + s[i] - '0';
	}
	return cur;
}

template<typename T>
concept HasOpOut =
    requires(T t) {
        { std::cout << t } -> std::same_as<std::ostream&>;
    };


template <class... ArgsT>
std::string make_format(const std::string &, std::vector<std::string> &, ArgsT&&...){
	throw Error::WrongArg;
}

#include "format.tpp"

template <class... ArgsT>
std::string format(const std::string &s, ArgsT&&... args){
	std::vector<std::string> v;
	try {
		return make_format(s, v, std::forward<ArgsT>(args)...);
	}
	catch (Error a){
		throw a;
	}
	return s;
}
