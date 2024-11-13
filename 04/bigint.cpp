#include<iostream>
#include<iomanip>
#include "bigint.hpp"

BigInt::BigInt() : size(1), negative(false) {
    data = new int[1]{0};
};
BigInt::BigInt(const std::string& number)
{
    negative = false;
    if (number.size() == 0)
    {
        size = 1;
        data = new int[1]{0};
        return;
    }
    size_t n = number.size();
    if (number[0] == '+' || number[0] == '-')
    {
        n--;
    }
    if (number[0] == '-')
    {
        negative = true;
    }
    while(n != 1 && number[number.size() - n] == '0')
    {
        n--;
    }
    if (n == 1 && number[number.size() - n] == '0' && negative)
    {
        negative = false;
    }
    size = (n - 1)/9 + 1;
    data = new int[size]{0};
    size_t cnt = 0;
    size_t block = 0;
    int tmp = 0, ten_pow = 1;
    for (size_t i = number.size(); i > number.size() - n; i--)
    {
        if ('0' <= number[i - 1] && number[i - 1] <= '9')
        {
            tmp = tmp + ten_pow * (number[i - 1] - '0');
            ten_pow *= 10;
        }
        else
        {
            size = 0;
            delete[] data;
            throw std::invalid_argument("String is incorrect number");
        }
        block++;
        if (block == 9)
        {
            ten_pow = 1;
            data[cnt] = tmp;
            cnt++;
            block = 0;
            tmp = 0;
        }
    }
    if (block)
    {
        data[cnt] = tmp;
        cnt++;
    }
}

BigInt::BigInt(const BigInt& rhs)
{
    size = rhs.size;
    negative = rhs.negative;
    data = new int[size];
    for(size_t i = 0; i < size; i++)
    {
        data[i] = rhs.data[i];
    }
}

BigInt& BigInt::operator = (const BigInt& rhs)
{
    size = rhs.size;
    negative = rhs.negative;
    int *tmp = new int[size];
    for(size_t i = 0; i < size; i++)
    {
        tmp[i] = rhs.data[i];
    }
    delete [] data;
    data = tmp;
    return *this;
}

BigInt::BigInt(BigInt&& rhs)
{
    size = rhs.size;
    negative = rhs.negative;
    data = rhs.data;
    rhs.size = 1;
    rhs.negative = false;
    rhs.data = new int[1]{0};
}

BigInt& BigInt::operator = (BigInt&& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    delete [] data;
    size = rhs.size;
    negative = rhs.negative;
    data = rhs.data;
    rhs.size = 1;
    rhs.negative = false;
    rhs.data = new int[1]{0};
    return *this;
}

bool BigInt::operator < (const BigInt& rhs) const
{
    if (negative && !rhs.negative)
    {
        return true;
    }
    if (!negative && rhs.negative)
    {
        return false;
    }
    bool change = false;
    if (negative && rhs.negative)
    {
        change = true;
    }
    size_t start = std::max(size, rhs.size);
    int l, r;
    for (size_t i = start; i > 0; i--)
    {
        l = 0;
        r = 0;
        if (i <= size)
        {
            l = data[i-1];
        }
        if (i <= rhs.size)
        {
            r = rhs.data[i-1];
        }
        if (l != r)
        {
            if (change)
            {
                return l > r;
            }
            return l < r;
        }
    }
    return false;
}

bool BigInt::operator > (const BigInt& rhs) const
{
    return rhs < *this;
}
bool BigInt::operator == (const BigInt& rhs) const
{
    if ((!negative && rhs.negative) || (negative && !rhs.negative))
    {
        return false;
    }
    size_t start = std::max(size, rhs.size);
    int l, r;
    for (size_t i = start; i > 0; i--)
    {
        l = 0;
        r = 0;
        if (i <= size)
        {
            l = data[i-1];
        }
        if (i <= rhs.size)
        {
            r = rhs.data[i-1];
        }
        if (l != r)
        {
            return false;
        }
    }
    return true;
}
bool BigInt::operator != (const BigInt& rhs) const
{
    return !(rhs == *this);
}
bool BigInt::operator <= (const BigInt& rhs) const
{
    return !(*this > rhs);
}
bool BigInt::operator >= (const BigInt& rhs) const
{
    return !(*this < rhs);
}

BigInt BigInt::operator - () const
{
    BigInt ans = *this;
    ans.negative = !ans.negative;
    ans.DeleteLeadingZeros();
    return ans;
}

BigInt BigInt::operator - (const BigInt& rhs) const
{
    if (!negative && !rhs.negative)
    {
        if (*this >= rhs)
        {
            BigInt ans;
            ans.size = size;
            ans.negative = negative;
            delete [] ans.data;
            ans.data = new int[ans.size]{0};
            int tmp = 0;
            for (size_t i = 0; i < ans.size; i++)
            {
                if (i < size && i < rhs.size)
                {
                    ans.data[i] = (base + data[i] - rhs.data[i] + tmp) % base;
                    tmp = -1 + (base + data[i] - rhs.data[i] + tmp) / base;
                }
                else if (i < size)
                {
                    ans.data[i] = (base + data[i] + tmp) % base;
                    tmp = -1 + (base + data[i] + tmp) / base;
                }
            }
            ans.DeleteLeadingZeros();
            return ans;
        }
        return -(rhs - *this);
    }
    if ((negative && rhs.negative))
    {
        return (-rhs) - (-*this);
    }
    return *this + (-rhs);
}

BigInt BigInt::operator + (const BigInt& rhs) const
{
    if ((negative && rhs.negative) || (!negative && !rhs.negative))
    {
        BigInt ans;
        ans.size = std::max(size, rhs.size) + 1;
        ans.negative = negative;
        delete [] ans.data;
        ans.data = new int[ans.size]{0};
        int tmp = 0;
        for (size_t i = 0; i < ans.size; i++)
        {
            if (i < size && i < rhs.size)
            {
                ans.data[i] = (data[i] + rhs.data[i] + tmp) % base;
                tmp = (data[i] + rhs.data[i] + tmp) / base;
            }
            else if (i < size)
            {
                ans.data[i] = (data[i] + tmp) % base;
                tmp = (data[i] + tmp) / base;
            }
            else if (i < rhs.size)
            {
                ans.data[i] = (rhs.data[i] + tmp) % base;
                tmp = (rhs.data[i] + tmp) / base;
            }
            else
            {
                ans.data[i] = tmp % base;
                tmp = tmp / base;
            }
        }
        ans.DeleteLeadingZeros();
        return ans;
    }
    return *this - (-rhs);
}

BigInt BigInt::operator * (const BigInt& rhs) const
{
    BigInt ans;

    if ((negative && !rhs.negative) || (!negative && rhs.negative))
    {
        ans.negative = true;
    }
    ans.size = size * rhs.size + 1;
    delete [] ans.data;
    ans.data = new int[ans.size]{0};
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < rhs.size; j++)
        {
            ans.data[i+j+1] += (static_cast<int64_t>(ans.data[i+j]) + static_cast<int64_t>(data[i]) * static_cast<int64_t>(rhs.data[j])) / base;
            ans.data[i+j] = (static_cast<int64_t>(ans.data[i+j]) + static_cast<int64_t>(data[i]) * static_cast<int64_t>(rhs.data[j])) % base;
        }
    }
    ans.DeleteLeadingZeros();
    return ans;
}
BigInt BigInt::operator + (const int& rhs) const
{
    return *this + BigInt(std::to_string(rhs));
}
BigInt BigInt::operator - (const int& rhs) const
{
    return *this - BigInt(std::to_string(rhs));
}
BigInt BigInt::operator * (const int& rhs) const
{
    return *this * BigInt(std::to_string(rhs));
}

BigInt::~BigInt()
{
    delete [] data;
    size = 0;
}

void BigInt::DeleteLeadingZeros()
{
    if (size == 0)
    {
        return;
    }
    size_t i = size;
    while(i > 1 && data[i - 1] == 0)
    {
        i--;
    }
    if (i == 1 && data[i - 1] == 0 && negative)
    {
        negative = false;
    }
    int *tmp = new int[i];
    for (size_t j = 0; j < i; j++)
    {
        tmp[j] = data[j];
    }
    delete [] data;
    data = tmp;
    size = i;
}

std::ostream& operator << (std::ostream& out, const BigInt& num)
{
    if (num.size == 0)
    {
        out << 0;
        return out;
    }
    if (num.negative)
    {
        out << '-';
    }
    size_t i = num.size;
    while(i > 1 && num.data[i - 1] == 0)
    {
        i--;
    }
    out << num.data[i - 1];
    i--;
    while(i)
    {
        out << std::setfill('0') << std::setw(9) << num.data[i - 1];
        i--;
    }
    return out;
}
