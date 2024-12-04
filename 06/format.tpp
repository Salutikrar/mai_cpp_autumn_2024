std::string make_format(const std::string &s, std::vector<std::string> &v){
	std::string s1 = "";
	for(size_t i = 0; i < s.size(); ++i){
		if(s[i] == '{'){
			++i;
			std::string num_s = "";
			while(i < s.size() && s[i] != '}'){
				if(s[i] < '0' || s[i] > '9'){
					throw Error::WrongContent;
				}
				num_s.push_back(s[i]);
				++i;
			}
			if(num_s.size() == 0){
				throw Error::EmptyNum;
			}
			size_t num = string_to_int(num_s);
			if(num >= v.size()){
				throw Error::WrongNum;
			}
			for(size_t j = 0; j < v[num].size() ; ++j){
				s1.push_back(v[num][j]);
			}
		}
		else if(s[i] == '}'){
			throw Error::WrongOpenBracket;
		}
		else {
			s1.push_back(s[i]);
		}
	}
	return s1;
}

template <HasOpOut T>
std::string make_format(const std::string &s, std::vector<std::string> &v, T&& cur){
	std::stringstream stream;
	stream << cur;
	v.push_back(stream.str());
	return make_format(s, v);
}

template <HasOpOut T, class... ArgsT>
std::string make_format(const std::string &s, std::vector<std::string> &v, T&& cur, ArgsT&&... args){
	std::stringstream stream;
	stream << cur;
	v.push_back(stream.str());
	return make_format(s, v, std::forward<ArgsT>(args)...);
}
