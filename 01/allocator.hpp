#pragma once
#include <iostream>
using namespace std;


class Allocator
{
public:
    bool flag;
    size_t offset;
    size_t mySize;
    char* myPointer;
    Allocator();
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    ~Allocator();
};