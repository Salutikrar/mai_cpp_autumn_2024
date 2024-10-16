#include <iostream>
#include <gtest/gtest.h>

#include "token.hpp"

class tokenTest : public ::testing::Test
{
protected:
    void SetUp()
    {
    }
    void TearDown()
    {
    }
};

TEST_F(tokenTest, parse_digit_token)
{
    TokenParser parser;
    bool digitTokenCalled = false;
    parser.SetDigitTokenCallback([&](const uint64_t& value)
    {
        EXPECT_EQ(value, 1234);
        digitTokenCalled = true;
    });

    parser.Parse("1234 beatngu");
    EXPECT_TRUE(digitTokenCalled);
}

TEST_F(tokenTest, parse_string_token)
{
    TokenParser parser;
    bool stringTokenCalled = false;
    parser.SetStringTokenCallback([&](const std::string& value)
    {
        EXPECT_EQ(value, "beatngu");
        stringTokenCalled = true;
    });

    parser.Parse("1234 beatngu");
    EXPECT_TRUE(stringTokenCalled);
}

TEST_F(tokenTest, token_statistics)
{
    TokenParser parser;
    int digitTokenCount = -1;
    int stringTokenCount = -1;
    int endWasHere = 0;

    parser.SetStartCallback([&]() {
        digitTokenCount = 0;
        stringTokenCount = 0;
    });
    parser.SetEndCallback([&]() {
        endWasHere = 1;

    });
    parser.SetDigitTokenCallback([&](const uint64_t&) {
        digitTokenCount++;
    });

    parser.SetStringTokenCallback([&](const std::string&) {
        stringTokenCount++;
    });

    parser.Parse("0000000000000000000000000000000000000001 4you 56789 18446744073709551616 18446744073709551615");

    EXPECT_EQ(digitTokenCount, 3);
    EXPECT_EQ(stringTokenCount, 2);
    EXPECT_EQ(endWasHere, 1);
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
