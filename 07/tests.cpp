#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include "avl.hpp"

class TestAvl : public ::testing::Test
{
protected:
		Avl<int, std::string> tree;
        void SetUp(){
                tree.insert({1, "one"});
				tree.insert({2, "two"});
				tree.insert({3, "three"});
        }
        void TearDown(){
                //std::cout << "TearDown" << '\n';
        }
};

TEST_F(TestAvl, InsertAndFind) {
    ASSERT_EQ(tree.size(), 3);
    auto findResult = tree.find(2);
    ASSERT_NE(findResult, nullptr);
    EXPECT_EQ((*findResult).second, "two");
}

TEST_F(TestAvl, OperatorSquareBrackets) {
    EXPECT_EQ(tree[1], "one");
    EXPECT_EQ(tree[2], "two");
    EXPECT_EQ(tree[3], "three");
}

TEST_F(TestAvl, AtMethod) {
    EXPECT_EQ(tree.at(2), "two");
}

TEST_F(TestAvl, Erase) {
    EXPECT_TRUE(tree.erase(2));
    EXPECT_FALSE(tree.erase(5));
}

TEST_F(TestAvl, Contains) {
    EXPECT_TRUE(tree.contains(1));
    EXPECT_FALSE(tree.contains(5));
}

TEST_F(TestAvl, EmptyAndSize) {
    EXPECT_FALSE(tree.empty());
    tree.clear();
    EXPECT_TRUE(tree.empty());
}

TEST_F(TestAvl, Iterators) {
    auto it = tree.begin();
    EXPECT_EQ((*it).second, "one");
    ++it;
    EXPECT_EQ((*it).second, "two");
    ++it;
    EXPECT_EQ((*it).second, "three");
}

TEST_F(TestAvl, SimpleTestAvl){
	Avl<int, int> m;
	m[5] = 5;
	ASSERT_EQ(m[5], 5);
	std::pair<int, int> p = {321, 1};
	m.insert(p);
	int v = m.at(321);
	ASSERT_EQ(v, 1);
	m.erase(5);
	ASSERT_NO_THROW(m.erase(5));
	ASSERT_EQ(m.size(), 1);
	for(int i = 100; i < 120 ; ++i){
		m[i] = i * 10;
	}
	ASSERT_EQ(m.size(), 21);
	ASSERT_EQ(m[111], 1110);
}

TEST_F(TestAvl, TestInsertEraseIter){
	Avl<char, std::string> m1;
	for(char i = 'a' ; i < 'v' ; ++i){
		std::string s = "";
		s.push_back(i);
		s.push_back('z');
		std::pair<char, std::string> p = {i, s};
		m1.insert(p);
	}
	ASSERT_EQ(m1.size(), 21);
	char a = 'a' - 1;
	auto it1 = m1.begin();
	for(auto it = m1.begin(); it != m1.end() ; ++it){
		a++;
		std::string s;
		s.push_back(a);
		s.push_back('z');
		ASSERT_EQ((*it).second, s);
		it1 = it;
	}
	for(auto it = it1; it != m1.begin() ; --it){
                std::string s;
                s.push_back(a);
                s.push_back('z');
                ASSERT_EQ((*it).second, s);
                it1 = it;
		a--;
        }
	a = 'v';
	for(auto it = m1.rbegin(); it != m1.rend() ; ++it){
		a--;
		std::string s;
		s.push_back(a);
		s.push_back('z');
		ASSERT_EQ((*it).second, s);
		it1 = it;
	}
	for(auto it = it1; it != m1.rbegin(); --it){
		std::string s;
                s.push_back(a);
                s.push_back('z');
                ASSERT_EQ((*it).second, s);
                it1 = it;
		a++;
	}
	for(char i = 'f'; i <= 'k'; ++i){
		m1.erase(i);
	}
	std::string s1;
	for(auto it = m1.begin(); it != m1.end() ; ++it){
		s1.push_back((*it).first);
	}
	ASSERT_EQ(s1, "abcdelmnopqrstu");
	while(true){
		bool fl = true;
		for(auto it = m1.begin(); it != m1.end() ; ++it){
			if((*it).first >= 'o' && (*it).first <= 's'){
				m1.erase(it);
				fl = false;
				break;
			}
		}
		if(fl){
			break;
		}
	}
	s1 = "";
	for(auto it = m1.begin(); it != m1.end() ; ++it){
                s1.push_back((*it).first);
        }
	ASSERT_EQ(s1, "abcdelmntu");
	for(char i = 'z' ; i >= 'v' ; --i){
		std::string s = "";
		s.push_back(i);
		s.push_back('z');
		m1[i] = s;
	}
	s1 = "";
        for(auto it = m1.begin(); it != m1.end() ; ++it){
                s1.push_back((*it).first);
        }
        ASSERT_EQ(s1, "abcdelmntuvwxyz");
	m1.erase('l');
	ASSERT_NO_THROW(m1.erase('l'));
	ASSERT_ANY_THROW(m1.erase(m1.end()));
	ASSERT_ANY_THROW(m1.erase(m1.rend()));
	ASSERT_ANY_THROW(++m1.end());
	ASSERT_ANY_THROW(++m1.rend());
	ASSERT_ANY_THROW(--m1.begin());
	ASSERT_ANY_THROW(--m1.rbegin());
}

TEST_F(TestAvl, TestFindAtSize){
	Avl<long long, bool> m2;
	size_t size = 0;
	for(long long i = 10; i < 200; i = i + 21){
		m2[i] = ((i % 2) == 1);
		++size;
	}
	ASSERT_EQ(m2.at(73), true);
	ASSERT_ANY_THROW(m2.at(1231231));
	auto it = m2.find(115);
	ASSERT_EQ((*it).first, 115);
	ASSERT_EQ(m2.find(1231231), m2.end());
	ASSERT_EQ(m2.contains(10), true);
	ASSERT_EQ(m2.contains(1231231), false);
	++it;
	ASSERT_NE(m2.find(136), m2.end());
	m2.erase(it);
	ASSERT_NO_THROW(m2.erase(136));
	--size;
	ASSERT_EQ(m2.find(136), m2.end());
	ASSERT_EQ(size, m2.size());
	ASSERT_EQ(m2.contains(31), true);
	m2.erase(31);
	--size;
	ASSERT_EQ(size, m2.size());
	m2.erase(31);
	ASSERT_EQ(m2.contains(31), false);
	ASSERT_EQ(size, m2.size());
	ASSERT_EQ(m2.empty(), false);
	m2.clear();
	ASSERT_EQ(m2.size(), 0);
	ASSERT_EQ(m2.empty(), true);
	m2[33] = true;
	ASSERT_EQ(m2.size(), 1);
	ASSERT_EQ(m2.empty(), false);
}

int main(int argc, char* argv[]){
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}
