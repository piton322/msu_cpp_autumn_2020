#pragma once
#include <iostream>
#include "iter.hpp"
#include "reiter.hpp"
#include "alloc.hpp"
#include "error.hpp"
using namespace std;


template <class T, class Allocator = MyAllocator<T>>
class Vect
{
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using ptr = T*;
    using iter_reference = MyIterator<value_type>&;
    using iter = MyIterator<value_type>;
    using r_iter = MyReIterator<value_type>;


    Vect(const size_t new_size): my_capacity(new_size), my_size(new_size),
                                 my_allocator()
    {
        if (new_size < 0)
        {
            throw Error::CreateError;
        }
        else
        {
            my_pointer = my_allocator.allocate(my_capacity);
        }
    }

    Vect(): my_capacity(0), my_size(0), my_pointer(nullptr), my_allocator(){}

    // rule_of_five
    // copy constructor
    Vect(const Vect& sec_vec): my_capacity(sec_vec.my_capacity),
                               my_size(sec_vec.my_size),
                               my_allocator()
    {
        my_pointer = my_allocator.allocate(my_capacity);
        for (auto i = 0; i < my_size; i++)
        {
            my_pointer[i] = sec_vec[i];
        }
    }

    // move constructor
    Vect(Vect&& sec_vec) noexcept: my_capacity(sec_vec.my_capacity),
                                   my_size(sec_vec.my_size),
                                   my_allocator()
    {
        my_pointer = my_allocator.allocate(my_capacity);
        for (auto i = 0; i < my_size; i++)
        {
            my_pointer[i] = move(sec_vec[i]);
        }
        sec_vec.my_size = 0;
        sec_vec.my_capacity = 0;
    }

    // copy assignment
    Vect & operator=(const Vect & sec_vec) noexcept
    {
        this->~Vect();
        my_size = sec_vec.size();
        my_capacity = sec_vec.capacity();
        my_pointer = my_allocator.allocate(my_capacity);
        for (auto i = 0; i < my_size; i++)
        {
            my_pointer[i] = sec_vec[i];
        }
        return * this;
    }

    // move assignment
    Vect & operator=(Vect && sec_vec)
    {
        this->~Vect();
        my_size = sec_vec.size();
        my_capacity = sec_vec.capacity();
        my_pointer = my_allocator.allocate(my_capacity);
        for (auto i = 0; i < my_size; i++)
        {
            my_pointer[i] = move(sec_vec[i]);
        }
        sec_vec.my_size = 0;
        sec_vec.my_capacity = 0;
        return * this;
    }

    //deallocate
    ~Vect()
    {
        my_size = 0;
        my_capacity = 0;
        if (my_pointer != nullptr)
        {
            my_allocator.deallocate(my_pointer);
        }
    }

    /* operator[], push_back, pop_back,
       emplace_back, empty, size, clear,
       begin, rbegin, end, rend, resize,
       reserve, capacity */

    reference operator[](size_t i)
    {
        if (i > my_size || i < 0)
        {
            throw Error::IndexError;
        }
        return my_pointer[i];
    }

    const_reference operator[](size_t i) const
    {
        if (i > my_size || i < 0)
        {
            throw Error::IndexError;
        }
        return my_pointer[i];
    }

    void push_back(const_reference new_value)
    {
        if (my_size >= my_capacity)
        {
            // на лекции говорилось, что память выделяется с запасом
            my_capacity = 2 * my_capacity + 1; // +1 для случая с my_capacity = 0
            reAlloc();
        }
        my_size++;
        my_pointer[my_size-1] = new_value;
    }

    void push_back(value_type && new_value)
    {
        if (my_size >= my_capacity)
        {
            my_capacity = 2 * my_capacity + 1;
            reAlloc();
        }
        my_size++;
        my_pointer[my_size-1] = move(new_value);
    }

    void reAlloc()
    {
        ptr new_pointer = my_allocator.allocate(my_capacity);
        for (auto i = 0; i < my_size; i++)
        {
            new_pointer[i] = move(my_pointer[i]);
        }
        my_pointer = new_pointer;
    }

    void pop_back()
    {
        if (my_size <= 0)
        {
            throw Error::IndexError;
        }
        my_size--;
        my_allocator.del(my_pointer + my_size);
    }

    template <class... ArgsT>
    void emplace_back(ArgsT&& ... args)
    {
        this->push_back(value_type(forward<ArgsT>(args)...));
    }

    bool empty() const
    {
        return my_size == 0;
    }

    size_t size() const
    {
        return my_size;
    }

    void clear()
    {
        allDel(0);
        my_size = 0;
    }

    void allDel(size_t s)
    {
        for (ptr p = my_pointer + s; p != my_pointer + my_size; p++)
        {
            my_allocator.del(p);
        }
    }

    iter begin()
    {
        return iter(my_pointer);
    }

    r_iter rbegin()
    {
        return r_iter(my_pointer + my_size);
    }

    iter end()
    {
        return iter(my_pointer + my_size);
    }

    r_iter rend()
    {
        return r_iter(my_pointer);
    }

    void resize(size_t new_size)
    {
        if (new_size < my_size)
        {
            allDel(new_size);
            my_size = new_size;
        }
        else
        {
            if (new_size > my_capacity)
            {
                my_capacity = new_size * 2 + 1;
                reAlloc();
            }
            my_size = new_size;
        }
    }

    void reserve(size_t new_size)
    {
        if (new_size > my_capacity)
        {
            my_capacity = new_size;
            reAlloc();
        }
        my_size = new_size;
    }

    size_t capacity() const
    {
        return my_capacity;
    }

private:
    size_t my_capacity;
    size_t my_size;
    ptr my_pointer;
    Allocator my_allocator;
};