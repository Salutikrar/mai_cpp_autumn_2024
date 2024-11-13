#include <iostream>
#pragma once

class BigInt
{
public:
    BigInt();
    BigInt(const std::string& number);
    BigInt(const BigInt& rhs);
    BigInt& operator = (const BigInt& rhs);
    BigInt(BigInt&& rhs);
    BigInt& operator = (BigInt&& rhs);
    bool operator < (const BigInt& rhs) const;
    bool operator > (const BigInt& rhs) const;
    bool operator == (const BigInt& rhs) const;
    bool operator != (const BigInt& rhs) const;
    bool operator <= (const BigInt& rhs) const;
    bool operator >= (const BigInt& rhs) const;
    friend std::ostream& operator << (std::ostream& out, const BigInt& num);
    BigInt operator - () const;
    BigInt operator - (const BigInt& rhs) const;
    BigInt operator + (const BigInt& rhs) const;
    BigInt operator * (const BigInt& rhs) const;
    BigInt operator + (const int& rhs) const;
    BigInt operator - (const int& rhs) const;
    BigInt operator * (const int& rhs) const;
    ~BigInt();

private:
    size_t size;
    int* data;
    const int base = 1000000000;
    bool negative;
    void DeleteLeadingZeros();
};
