#include <iostream>
#include <gtest/gtest.h>

#include "bigint.hpp"

class BigIntTest : public ::testing::Test
{
protected:
    void SetUp()
    {
    }
    void TearDown()
    {
    }
};

TEST_F(BigIntTest, DefaultConstructor) {
    BigInt defaultBigInt;
    EXPECT_EQ(defaultBigInt, BigInt("0"));
}

TEST_F(BigIntTest, StringConstructor) {
    BigInt bigIntFromString("123456789012345678901234567890");
    std::stringstream buffer;
    buffer << bigIntFromString;
    EXPECT_EQ(buffer.str(), "123456789012345678901234567890");
    buffer.clear();
    buffer.str("");
    BigInt bigIntFromStringWithLeadingZeros("-000009876543210");
    buffer << bigIntFromStringWithLeadingZeros;
    EXPECT_EQ(buffer.str(), "-9876543210");
    buffer.clear();
    buffer.str("");
    BigInt bigIntFromStringZero("+00000");
    buffer << bigIntFromStringZero;
    EXPECT_EQ(buffer.str(), "0");
    buffer.clear();
    buffer.str("");
    BigInt bigIntFromStringEmpty("");
    buffer << bigIntFromStringEmpty;
    EXPECT_EQ(buffer.str(), "0");
}

TEST_F(BigIntTest, CopyConstructor) {
    BigInt a{"123456789012345678901234567890"};
    BigInt copiedBigInt(a);
    EXPECT_EQ(copiedBigInt, a);
}

TEST_F(BigIntTest, CopyOperator) {
    BigInt a{"123456789012345678901234567890"};
    BigInt b;
    b = a;
    EXPECT_EQ(b, a);
    BigInt c("-1");
    a = c;
    EXPECT_EQ(c, a);
    c = c;
    EXPECT_EQ(c, BigInt("-1"));
}

TEST_F(BigIntTest, MoveConstructor) {
    BigInt b{"987654321098765432109876543210"};
    BigInt movedBigInt(std::move(b));
    EXPECT_EQ(b, BigInt("0"));
    EXPECT_EQ(movedBigInt, BigInt("987654321098765432109876543210"));
}

TEST_F(BigIntTest, MoveOperator) {
    BigInt b{"-987654321098765432109876543210"};
    BigInt movedBigInt("-123");
    movedBigInt = std::move(b);
    EXPECT_EQ(movedBigInt, BigInt("-987654321098765432109876543210"));
    EXPECT_EQ(b, BigInt("0"));
}

TEST_F(BigIntTest, LessThanOperator) {
    BigInt c{"1234567890"};
    BigInt b{"987654321098765432109876543210"};
    BigInt d{"987654321098765432109876543210"};
    BigInt e{"-987654321098765432109876543210"};
    BigInt f{"-999999999999999999999999999999"};
    BigInt g{"0"};
    EXPECT_TRUE(c < b);
    EXPECT_FALSE(b < c);
    EXPECT_FALSE(b < d);
    EXPECT_TRUE(f < e);
    EXPECT_FALSE(e < f);
    EXPECT_TRUE(e < g);
    EXPECT_FALSE(g < e);
    EXPECT_TRUE(g < c);
}

TEST_F(BigIntTest, GreaterThanOperator) {
    BigInt c{"1234567890"};
    BigInt b{"987654321098765432109876543210"};
    BigInt d{"987654321098765432109876543210"};
    BigInt e{"-987654321098765432109876543210"};
    BigInt f{"-999999999999999999999999999999"};
    BigInt g{"0"};
    EXPECT_FALSE(c > b);
    EXPECT_TRUE(b > c);
    EXPECT_FALSE(b > d);
    EXPECT_FALSE(f > e);
    EXPECT_TRUE(e > f);
    EXPECT_FALSE(e > g);
    EXPECT_TRUE(g > e);
    EXPECT_FALSE(g > c);
}

TEST_F(BigIntTest, EqualsOperator) {
    BigInt d{"123456789012345678901234567890"};
    BigInt a{"123456789012345678901234567890"};
    EXPECT_TRUE(d == a);
    BigInt e{"123456789012345678901234567890"};
    BigInt f{"-123456789012345678901234567890"};
    EXPECT_FALSE(e == f);
    BigInt g{"-123456789"};
    BigInt h{"-123456789012345678901234567890"};
    EXPECT_FALSE(g == h);
}

TEST_F(BigIntTest, NotEqualsOperator) {
    BigInt c{"1234567890"};
    BigInt b{"987654321098765432109876543210"};
    EXPECT_TRUE(c != b);
    BigInt d{"123456789012345678901234567890"};
    BigInt a{"123456789012345678901234567890"};
    EXPECT_FALSE(d != a);
    BigInt e{"123456789012345678901234567890"};
    BigInt f{"-123456789012345678901234567890"};
    EXPECT_TRUE(e != f);
    BigInt g{"-123456789"};
    BigInt h{"-123456789012345678901234567890"};
    EXPECT_TRUE(g != h);
}

TEST_F(BigIntTest, LessThanOrEqualOperator) {
    BigInt a{"123456789012345678901234567890"};
    BigInt c{"1234567890"};
    BigInt b{"987654321098765432109876543210"};
    BigInt d{"987654321098765432109876543210"};
    BigInt e{"-987654321098765432109876543210"};
    BigInt f{"-999999999999999999999999999999"};
    BigInt g{"0"};
    EXPECT_TRUE(c <= a);
    EXPECT_TRUE(c <= b);
    EXPECT_FALSE(b <= c);
    EXPECT_TRUE(b <= d);
    EXPECT_TRUE(f <= e);
    EXPECT_FALSE(e <= f);
    EXPECT_TRUE(e <= g);
    EXPECT_FALSE(g <= e);
    EXPECT_TRUE(g <= c);
}

TEST_F(BigIntTest, GreaterThanOrEqualOperator) {
    BigInt a{"123456789012345678901234567890"};
    BigInt c{"1234567890"};
    BigInt b{"987654321098765432109876543210"};
    BigInt d{"987654321098765432109876543210"};
    BigInt e{"-987654321098765432109876543210"};
    BigInt f{"-999999999999999999999999999999"};
    BigInt g{"0"};
    EXPECT_FALSE(c >= a);
    EXPECT_FALSE(c >= b);
    EXPECT_TRUE(b >= c);
    EXPECT_TRUE(b >= d);
    EXPECT_FALSE(f >= e);
    EXPECT_TRUE(e >= f);
    EXPECT_FALSE(e >= g);
    EXPECT_TRUE(g >= e);
    EXPECT_FALSE(g >= c);
}

TEST_F(BigIntTest, UnaryMinusOperator) {
    BigInt c{"1234567890"};
    EXPECT_EQ(-c, BigInt("-1234567890"));
    BigInt a{"0"};
    EXPECT_EQ(-a, BigInt("0"));
    BigInt b{"-1234567890"};
    EXPECT_EQ(-b, BigInt("1234567890"));
    BigInt e{"-0"};
    EXPECT_EQ(-e, BigInt("-0"));
}

TEST_F(BigIntTest, AdditionOperator) {
    BigInt a{"123456789012345678901234567890"};
    BigInt b{"987654321098765432109876543210"};
    BigInt result = a + b;
    EXPECT_EQ(result, BigInt("1111111110111111111011111111100"));
    a = BigInt("-0");
    b = BigInt("12345678901234567890");
    result = a + b;
    EXPECT_EQ(result, BigInt("12345678901234567890"));
    a = BigInt("-12345678901234567890");
    b = BigInt("12345678901234567890");
    result = a + b;
    EXPECT_EQ(result, BigInt("0"));
    a = BigInt("-12341234123412341234");
    b = BigInt("-12341234123412341234");
    result = a + b;
    EXPECT_EQ(result, BigInt("-24682468246824682468"));
    a = BigInt("-999999999999999999");
    b = BigInt("1000000000000000000");
    result = a + b;
    EXPECT_EQ(result, BigInt("1"));
    a = BigInt("1000000000000000000");
    b = BigInt("-999999999999999999");
    result = a + b;
    EXPECT_EQ(result, BigInt("1"));
    a = BigInt("-1000000000000000000");
    b = BigInt("999999999999999999");
    result = a + b;
    EXPECT_EQ(result, BigInt("-1"));
}

TEST_F(BigIntTest, SubtractionOperator) {
    BigInt a{"987654321098765432109876543210"};
    BigInt b{"123456789012345678901234567890"};
    BigInt result = a - b;
    EXPECT_EQ(result, BigInt("864197532086419753208641975320"));
    a = BigInt("-0");
    b = BigInt("12345678901234567890");
    result = a - b;
    EXPECT_EQ(result, BigInt("-12345678901234567890"));
    a = BigInt("12345678901234567890");
    b = BigInt("12345678901234567890");
    result = a - b;
    EXPECT_EQ(result, BigInt("0"));
    a = BigInt("12341234123412341234");
    b = BigInt("-12341234123412341234");
    result = a - b;
    EXPECT_EQ(result, BigInt("24682468246824682468"));
    a = BigInt("999999999999999999");
    b = BigInt("1000000000000000000");
    result = a - b;
    EXPECT_EQ(result, BigInt("-1"));
    a = BigInt("1000000000000000000");
    b = BigInt("999999999999999999");
    result = a - b;
    EXPECT_EQ(result, BigInt("1"));
    a = BigInt("-1000000000000000000");
    b = BigInt("999999999999999999");
    result = a - b;
    EXPECT_EQ(result, BigInt("-1999999999999999999"));
}

TEST_F(BigIntTest, MultiplicationOperator) {
    BigInt a{"1234567890"};
    BigInt b{"2469135780"};
    BigInt result = a * b;
    EXPECT_EQ(result, BigInt("3048315750038104200"));
    a = BigInt("-0");
    b = BigInt("12345678901234567890");
    result = a * b;
    EXPECT_EQ(result, BigInt("0"));
    a = BigInt("-9999999999999999999999");
    b = BigInt("9999999999999999999999");
    result = a * b;
    EXPECT_EQ(result, BigInt("-99999999999999999999980000000000000000000001"));
    a = BigInt("-9999999999999999999999");
    b = BigInt("-9999999999999999999999");
    result = a * b;
    EXPECT_EQ(result, BigInt("99999999999999999999980000000000000000000001"));
    a = BigInt("999999999999999999");
    b = BigInt("1000000000000000000");
    result = a * b;
    EXPECT_EQ(result, BigInt("999999999999999999000000000000000000"));
    a = BigInt("1");
    b = BigInt("-999999999999999999");
    result = a * b;
    EXPECT_EQ(result, BigInt("-999999999999999999"));
    a = BigInt("-0");
    b = BigInt("0");
    result = a * b;
    EXPECT_EQ(result, BigInt("0"));
}

TEST_F(BigIntTest, AdditionWithInt) {
    BigInt a{"123456789012345678901234567890"};
    BigInt result = a + 1000;
    EXPECT_EQ(result, BigInt("123456789012345678901234568890"));
    a = BigInt("-1000000000000000000");
    result = a + 1;
    EXPECT_EQ(result, BigInt("-999999999999999999"));
}

TEST_F(BigIntTest, SubtractionWithInt) {
    BigInt a{"123456789012345678901234567890"};
    BigInt result = a - 1000;
    EXPECT_EQ(result, BigInt("123456789012345678901234566890"));
    a = BigInt("0");
    result = a - 999999999;
    EXPECT_EQ(result, BigInt("-999999999"));
}

TEST_F(BigIntTest, MultiplicationWithInt) {
    BigInt a{"123456789012345678901234567890"};
    BigInt result = a * 2;
    EXPECT_EQ(result, BigInt("246913578024691357802469135780"));
    a = BigInt("0");
    result = a * 999999999;
    EXPECT_EQ(result, BigInt("0"));
    a = BigInt("-1000000000000000000");
    result = a * 999999999;
    EXPECT_EQ(result, BigInt("-999999999000000000000000000"));
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
