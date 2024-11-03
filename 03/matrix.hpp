#include <iostream>
#pragma once

class Matrix
{
    class Row
    {
    private:
        int* data = nullptr;
        size_t cols = 0;

    public:
        Row();
        Row(int* data, size_t cols);
        int& operator[](size_t col);
        int* getAdress() const;
    };

public:
    Matrix(const size_t rows, const size_t cols);
    size_t getRows() const;
    size_t getColumns() const;
    Row& operator[](size_t i);
    Matrix& operator *=(int k);
    Matrix operator +(const Matrix& rhs) const;
    bool operator ==(const Matrix& rhs) const;
    bool operator !=(const Matrix& rhs) const;
    friend std::ostream& operator << (std::ostream& out, const Matrix& rhs);
    ~Matrix();

private:
    Row *matrix = nullptr;
    size_t rows = 0;
    size_t cols = 0;
};
