#include<iostream>
#include "matrix.hpp"

int main()
{
    const size_t rows = 5;
    const size_t cols = 3;

    Matrix m(rows, cols);

    std::cout << (m.getRows() == 5) << '\n';
    std::cout << (m.getColumns() == 3) << '\n';

    m[1][2] = 5; // строка 1, колонка 2
    double x = m[4][1];
    std::cout << x << " " << m[1][2] << '\n';
    m *= 3; // умножение на число

    Matrix m1(rows, cols);

    if (m1 == m)
    {
    }
    Matrix m2 = m1 + m;
    std::cout << m2 << std::endl;
}
