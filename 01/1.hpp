#ifndef __1_HPP__
#define __1_HPP__
#include <iostream>
using namespace std;


class Allocator
{
private:
    bool flag;
public:
    size_t offset;
    size_t mySize;
    char* myPointer;
    Allocator();
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    ~Allocator();
};
#endif