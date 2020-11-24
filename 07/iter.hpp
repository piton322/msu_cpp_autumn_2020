#pragma once
#include "error.hpp"
#include "vect.hpp"
using namespace std;


template <class T>
class MyIterator
{
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using ptr = T*;
    using iter_reference = MyIterator<value_type>&;
    using iter = MyIterator<value_type>;
    using const_iter_reference = const MyIterator<value_type>&;


    MyIterator(ptr pointer): my_ptr(pointer) {}

    reference operator *()
    {
        return * my_ptr;
    }

    const_reference operator *() const
    {
        return * my_ptr;
    }

    reference operator [] (const size_t i)
    {
        return my_ptr[i];
    }

    const_reference operator [] (const size_t i) const
    {
        return my_ptr[i];
    }

    iter_reference operator ++ ()
    {
        ++my_ptr;
        return * this;
    }

    iter_reference operator -- ()
    {
        --my_ptr;
        return * this;
    }

    iter operator ++ (int)
    {
        iter save = * this;
        ++my_ptr;
        return save;
    }

    iter operator -- (int)
    {
        iter save = * this;
        --my_ptr;
        return save;
    }

    bool operator > (const_iter_reference it) const
    {
        return my_ptr > it.my_ptr;
    }

    bool operator == (const_iter_reference it) const
    {
        return my_ptr == it.my_ptr;
    }

    bool operator >= (const_iter_reference it) const
    {
        return my_ptr >= it.my_ptr;
    }

    bool operator < (const_iter_reference it) const
    {
        return !(* this >= it);
    }

    bool operator <= (const_iter_reference it) const
    {
        return !(* this > it);
    }

    bool operator != (const_iter_reference it) const
    {
        return !(* this == it);
    }

    iter_reference operator += (int value)
    {
        my_ptr += value;
        return * this;
    }

    iter_reference operator -= (int value)
    {
        my_ptr -= value;
        return * this;
    }

    iter operator + (int value)
    {
        iter save = * this;
        return save + value;
    }

    iter operator - (int value)
    {
        iter save = * this;
        return save - value;
    }

private:
    ptr my_ptr;
};

