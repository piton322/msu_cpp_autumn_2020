#pragma once


template <class T>
class MyAllocator
{
public:
    using size_type = size_t;
    using value_type = T;
    using ptr = T*;


    ptr allocate(size_type size)
    {
        return new value_type[size];
    }

    void deallocate(ptr pointer)
    {
        delete[] pointer;
    }

    void del(ptr pointer) 
    {
        pointer->~value_type();
    }
};