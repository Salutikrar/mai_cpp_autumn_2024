#include <iostream>
#include "matrix.hpp"

Matrix::Row::Row() = default;

Matrix::Row::Row(int* data, size_t cols) : data(data), cols(cols)
{
}

int& Matrix::Row::operator[](size_t col)
{
    if (col >= cols)
    {
        throw std::out_of_range("Column index out of range");
    }
    return data[col];
}

int* Matrix::Row::getAdress() const
{
    return data;
}

Matrix::Matrix(const size_t rows, const size_t cols): rows(rows), cols(cols)
{
    matrix = new Row[rows];
    for (size_t i = 0; i < rows; i++)
    {
        matrix[i] = Row(new int[cols](), cols);
    }
}

size_t Matrix::getRows() const
{
    return rows;
}

size_t Matrix::getColumns() const
{
    return cols;
}

Matrix::Row& Matrix::operator[](size_t i)
{
    if (i >= rows)
    {
        throw std::out_of_range("Row index out of range");
    }
    return matrix[i];
}

Matrix& Matrix::operator *=(int k)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            matrix[i][j] *= k;
        }
    }
    return *this;
}

Matrix Matrix::operator +(const Matrix& rhs) const
{
    if (rows != rhs.rows || cols != rhs.cols)
    {
        throw std::invalid_argument("Matrix sizes do not match for addition");
    }
    Matrix ans(rows, cols);
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            ans.matrix[i][j] = matrix[i][j] + rhs.matrix[i][j];
        }
    }
    return ans;
}

bool Matrix::operator ==(const Matrix& rhs) const
{
    if (rows != rhs.rows || cols != rhs.cols)
    {
        return false;
    }
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            if (matrix[i][j] != rhs.matrix[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator !=(const Matrix& rhs) const
{
    return !(*this == rhs);
}

std::ostream& operator << (std::ostream& out, const Matrix& rhs)
{
    for(size_t i = 0;  i < rhs.rows; i++)
    {
        for (size_t j = 0; j < rhs.cols; j++)
        {
            out << rhs.matrix[i][j] << " ";
        }
        out << std::endl;
    }
    return out;
}

Matrix::~Matrix()
{
    for (size_t i = 0; i < rows; ++i)
    {
        delete[] matrix[i].getAdress();
    }
    delete [] matrix;
}
