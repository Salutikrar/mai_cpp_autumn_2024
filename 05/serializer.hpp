#include <iostream>
#include <sstream>
#include <string>
#include <stdint.h>

#pragma once

enum class Error
{
    NoError,
    CorruptedArchive,
    InvalidType,
    TypeMismatch
};

class Serializer
{
    static constexpr char Separator = ' ';

public:
    explicit Serializer(std::ostream& out);

    template <class T>
    Error save(T& object);

    template <class... ArgsT>
    Error operator()(ArgsT&&... args);

private:
    std::ostream& out_;

    Error process(bool& arg);

    Error process(uint64_t& arg);

    template <class T>
    Error process(T&& );

    template <class T, class... Args>
    Error process(T&& val, Args&&... args);
};

class Deserializer
{
public:
    explicit Deserializer(std::istream& in);

    template <class T>
    Error load(T& object);

    template <class... ArgsT>
    Error operator()(ArgsT&&... args);


private:
    std::istream& in_;

    Error process(bool& value);

    Error process(uint64_t& value);

    template <class T>
    Error process(T&& );

    template <class T, class... Args>
    Error process(T&& val, Args&&... args);
};



#include "serializer.tpp"
