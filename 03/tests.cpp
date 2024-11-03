#include <iostream>
#include <gtest/gtest.h>

#include "matrix.hpp"

class MatrixTest : public ::testing::Test
{
protected:
    const size_t rows = 4;
    const size_t cols = 3;
    Matrix matrix;

    MatrixTest() : matrix(rows, cols)
    {
        matrix[0][0] = 1; matrix[0][1] = 2; matrix[0][2] = 3;
        matrix[1][0] = 4; matrix[1][1] = 5; matrix[1][2] = 6;
        matrix[2][0] = 7; matrix[2][1] = 8; matrix[2][2] = 9;
        matrix[3][0] = 10; matrix[3][1] = 11; matrix[3][2] = 12;
    }
    void SetUp()
    {
    }
    void TearDown()
    {
    }
};


TEST_F(MatrixTest, checking_gets)
{
    ASSERT_EQ(matrix.getRows(), 4);
    ASSERT_EQ(matrix.getColumns(), 3);
}

TEST_F(MatrixTest, checking_access_and_changing)
{
    ASSERT_EQ(matrix[1][2], 6);
    matrix[1][2] = 10;
    ASSERT_EQ(matrix[1][2], 10);
}

TEST_F(MatrixTest, chacking_exceptions)
{
    ASSERT_THROW(matrix[4][0], std::out_of_range);
    ASSERT_THROW(matrix[0][3], std::out_of_range);
}

TEST_F(MatrixTest, checking_mult)
{
    matrix *= 2;
    ASSERT_EQ(matrix[0][0], 2);
    ASSERT_EQ(matrix[0][1], 4);
    ASSERT_EQ(matrix[0][2], 6);
    ASSERT_EQ(matrix[1][0], 8);
    ASSERT_EQ(matrix[1][1], 10);
    ASSERT_EQ(matrix[1][2], 12);
    ASSERT_EQ(matrix[2][0], 14);
    ASSERT_EQ(matrix[2][1], 16);
    ASSERT_EQ(matrix[2][2], 18);
    ASSERT_EQ(matrix[3][0], 20);
    ASSERT_EQ(matrix[3][1], 22);
    ASSERT_EQ(matrix[3][2], 24);
}

TEST_F(MatrixTest, checking_add)
{
    Matrix matrix2(4, 3);
    matrix2[0][0] = 1; matrix2[0][1] = 1; matrix2[0][2] = 1;
    matrix2[1][0] = 1; matrix2[1][1] = 1; matrix2[1][2] = 1;
    matrix2[2][0] = 1; matrix2[2][1] = 1; matrix2[2][2] = 1;
    matrix2[3][0] = 1; matrix2[3][1] = 1; matrix2[3][2] = 1;

    Matrix result = matrix + matrix2;
    ASSERT_EQ(result[0][0], 2);
    ASSERT_EQ(result[0][1], 3);
    ASSERT_EQ(result[0][2], 4);
    ASSERT_EQ(result[1][0], 5);
    ASSERT_EQ(result[1][1], 6);
    ASSERT_EQ(result[1][2], 7);
    ASSERT_EQ(result[2][0], 8);
    ASSERT_EQ(result[2][1], 9);
    ASSERT_EQ(result[2][2], 10);
    ASSERT_EQ(result[3][0], 11);
    ASSERT_EQ(result[3][1], 12);
    ASSERT_EQ(result[3][2], 13);
    Matrix matrix3(1, 1);
    ASSERT_THROW(matrix3 + matrix, std::invalid_argument);
}

TEST_F(MatrixTest, checking_equal)
{
    Matrix matrix2(4, 3);
    matrix2[0][0] = 2; matrix2[0][1] = 4; matrix2[0][2] = 6;
    matrix2[1][0] = 8; matrix2[1][1] = 10; matrix2[1][2] = 12;
    matrix2[2][0] = 14; matrix2[2][1] = 16; matrix2[2][2] = 18;
    matrix2[3][0] = 20; matrix2[3][1] = 22; matrix2[3][2] = 24;
    ASSERT_FALSE(matrix == matrix2);
    matrix *= 2;
    ASSERT_TRUE(matrix == matrix2);
    Matrix matrix3(1, 1);
    ASSERT_FALSE(matrix == matrix3);
}

TEST_F(MatrixTest, checking_inequal)
{
    Matrix matrix2(4, 3);
    matrix2[0][0] = 2; matrix2[0][1] = 4; matrix2[0][2] = 6;
    matrix2[1][0] = 8; matrix2[1][1] = 10; matrix2[1][2] = 12;
    matrix2[2][0] = 14; matrix2[2][1] = 16; matrix2[2][2] = 18;
    matrix2[3][0] = 20; matrix2[3][1] = 22; matrix2[3][2] = 24;
    ASSERT_TRUE(matrix != matrix2);
    matrix *= 2;
    ASSERT_FALSE(matrix != matrix2);
    Matrix matrix3(1, 1);
    ASSERT_TRUE(matrix != matrix3);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
