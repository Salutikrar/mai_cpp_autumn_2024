#include <iostream>
#pragma once
class Allocator
{
public:
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    ~Allocator();
private:
    char* buffer = nullptr;
    size_t offset = 0;
    size_t allocatorSize = 0;
};
