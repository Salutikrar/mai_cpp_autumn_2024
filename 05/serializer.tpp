#include "serializer.hpp"

Serializer::Serializer(std::ostream& out) : out_(out) {}

template <class T>
Error Serializer::save(T& object)
{
    out_.clear();
    out_.seekp(0);
    return object.serialize(*this);
}

template <class... ArgsT>
Error Serializer::operator()(ArgsT&&... args)
{
    return process(args...);
}

Error Serializer::process(bool& arg)
{
    out_ << (arg ? "true" : "false") << Separator;
    return Error::NoError;
}

Error Serializer::process(uint64_t& arg)
{
    out_ << arg << Separator;
    return Error::NoError;
}

template <class T>
Error Serializer::process(T&& )
{
    return Error::InvalidType;
}

template <class T, class... Args>
Error Serializer::process(T&& val, Args&&... args)
{
    if (process(val) != Error::NoError)
        return Error::InvalidType;
    return process(std::forward<Args>(args)...);
}

Deserializer::Deserializer(std::istream& in) : in_(in) {}

template <class T>
Error Deserializer::load(T& object)
{
    in_.seekg(0);
    return object.serialize(*this);
}

template <class... ArgsT>
Error Deserializer::operator()(ArgsT&&... args)
{
    return process(args...);
}

Error Deserializer::process(bool& value)
{
    std::string text;
    if (!(in_ >> text))
    {
        return Error::TypeMismatch;
    }

    if (text == "true")
    {
        value = true;
    }
    else if (text == "false")
    {
        value = false;
    }
    else
    {
        return Error::CorruptedArchive;
    }

    return Error::NoError;
}

Error Deserializer::process(uint64_t& value)
{
    std::string text;
    if (!(in_ >> text))
    {
        return Error::TypeMismatch;
    }

    try
    {
        value = std::stoull(text);
    } catch (const std::invalid_argument&)
    {
        return Error::CorruptedArchive;
    } catch (const std::out_of_range&)
    {
        return Error::CorruptedArchive;
    }

    return Error::NoError;
}

template <class T>
Error Deserializer::process(T&& )
{
    return Error::InvalidType;
}

template <class T, class... Args>
Error Deserializer::process(T&& val, Args&&... args)
{
    Error error = process(val);
    if (error != Error::NoError)
        return error;
    return process(std::forward<Args>(args)...);
}
