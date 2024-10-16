#include<iostream>
#include<functional>
#include <cstdint>
#include <limits>
#include "token.hpp"


TokenParser::TokenParser():
    digitTokenCallback(nullptr),
    stringTokenCallback(nullptr),
    startCallback(nullptr),
    endCallback(nullptr)
{
}

void TokenParser::SetStartCallback(std::function<void(void)> callback)
{
    startCallback = callback;
}
void TokenParser::SetEndCallback(std::function<void(void)> callback)
{
    endCallback = callback;
}
void TokenParser::SetDigitTokenCallback(std::function<void(const uint64_t&)> callback)
{
    digitTokenCallback = callback;
}
void TokenParser::SetStringTokenCallback(std::function<void(const std::string&)> callback)
{
    stringTokenCallback = callback;
}

void TokenParser::Parse(const std::string & str)
{
    if (startCallback != nullptr)
    {
        startCallback();
    }
    std::string tokenString = "";
    uint64_t tokenNumber;
    size_t cntLeadingZero = 0;
    bool notFoundLetters = true;
    for (char c : str + " ")
    {
        if (isdigit(c))
        {
            if (c == '0' && cntLeadingZero == tokenString.size())
            {
                ++cntLeadingZero;
            }
            tokenString += c;
        }
        else if (c == ' ' || c == '\n' || c == '\t')
        {
            if (tokenString.size() == 0)
            {
                continue;
            }
            if (notFoundLetters)
            {
                size_t maxDigitsUint64 = std::numeric_limits<uint64_t>::digits10 + 1;
                uint64_t maxNumberUint64 = std::numeric_limits<uint64_t>::max();
                if (tokenString.size() - cntLeadingZero == 0)
                {
                    --cntLeadingZero;
                }
                if ((tokenString.size() - cntLeadingZero) < maxDigitsUint64 || ((tokenString.size() - cntLeadingZero) == maxDigitsUint64 && tokenString <= std::to_string(maxNumberUint64)))
                {
                    tokenNumber = std::stoull(tokenString);
                    if (digitTokenCallback)
                    {
                        digitTokenCallback(tokenNumber);
                    }
                }
                else
                {
                    if (stringTokenCallback)
                    {
                        stringTokenCallback(tokenString);
                    }
                }

            }
            else
            {
                if (stringTokenCallback)
                {
                    stringTokenCallback(tokenString);
                }
            }
            notFoundLetters = true;
            tokenString = "";
            cntLeadingZero = 0;
        }
        else
        {
            notFoundLetters = false;
            tokenString += c;
        }
    }
    if (endCallback != nullptr)
    {
        endCallback();
    }
}
