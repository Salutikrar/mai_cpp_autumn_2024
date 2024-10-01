#include <iostream>
#include "allocator.hpp"

void Allocator::makeAllocator(size_t maxSize)
{
    delete[] buffer;
    buffer = new (std::nothrow) char[maxSize];
    if (buffer == nullptr)
    {
        throw std::bad_alloc();
    }
    allocatorSize = maxSize;
    offset = 0;
}

char* Allocator::alloc(size_t size)
{
    if (offset + size > allocatorSize)
        return nullptr;
    char* ptr = buffer + offset;
    offset += size;
    return ptr;
}

void Allocator::reset()
{
    offset = 0;
}

Allocator::~Allocator()
{
    delete[] buffer;
}
