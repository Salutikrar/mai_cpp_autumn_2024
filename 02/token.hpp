#include <iostream>
#include<functional>
#pragma once

class TokenParser
{
public:
    TokenParser();
    void SetStartCallback(std::function<void(void)> callback);
    void SetEndCallback(std::function<void(void)> callback);
    void SetDigitTokenCallback(std::function<void(const uint64_t)> callback);
    void SetStringTokenCallback(std::function<void(const std::string&)> callback);
    void Parse(const std::string & str);

private:
    std::function<void(const uint64_t)> digitTokenCallback;
    std::function<void(const std::string&)> stringTokenCallback;
    std::function<void(void)> startCallback;
    std::function<void(void)> endCallback;
};
