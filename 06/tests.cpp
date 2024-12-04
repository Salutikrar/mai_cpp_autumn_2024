#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include "format.hpp"

class FormatTest : public ::testing::Test
{
protected:
        void SetUp(){
                //std::cout << "SetUp" << '\n';
        }
        void TearDown(){
                //std::cout << "TearDown" << '\n';
        }
};

TEST_F(FormatTest, BasicFormatting){
	EXPECT_EQ(format("{0} + {1} = {2}", 1, 2, 3), "1 + 2 = 3");
    EXPECT_EQ(format("{0} + {0} = {1}", 2, 4), "2 + 2 = 4");
    EXPECT_EQ(format("Hello, {0}!", "World"), "Hello, World!");
    EXPECT_EQ(format("Value: {0}", 42), "Value: 42");
}

TEST_F(FormatTest, UnmatchedCurlyBraces) {
    ASSERT_ANY_THROW(format("{0} and {1", "test"));
    ASSERT_ANY_THROW(format("{0} and {1}}", "test"));
	ASSERT_ANY_THROW(format("Is {3} {0} {1}, or {} can 2 {0}?", "exist", true, false, 1));
	ASSERT_ANY_THROW(format("Is {3} {{0} {1}, or {2} can 2 {0}?", "exist", true, false, 1));
	ASSERT_ANY_THROW(format("Is {3} {0} {{{0}}} {1}, or {2} can 2 {0}?", "exist", true, false, 1));
}

TEST_F(FormatTest, IndexOutOfRange) {
    ASSERT_ANY_THROW(format("{1}", "only one"));
    ASSERT_ANY_THROW(format("{2}", "one", "two"));
}

TEST_F(FormatTest, InvalidIndex) {
    ASSERT_ANY_THROW(format("Invalid {x}", "test"));
}

TEST_F(FormatTest, MixedFormatting) {
    EXPECT_EQ(format("Values: {0}, {1}, and {2}", 1, "two", 3.0), "Values: 1, two, and 3");
}

int main(int argc, char* argv[]){
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}
