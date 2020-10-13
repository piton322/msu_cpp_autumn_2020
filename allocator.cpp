#include <iostream>
#include "allocator.hpp"
using namespace std;


Allocator::Allocator()
{
    myPointer = nullptr;
    flag = false;
    offset = 0;
    mySize = 0;
}


void Allocator::makeAllocator(size_t maxSize)
{
    bad_alloc exception;
    try
    {
        if (maxSize <= 0)
        {
            throw exception;
        }
        if (flag == false)
        {
            // флаг, чтобы не делали 2 раза makeAllocator
            offset = 0;
            mySize = maxSize;
            myPointer = new char[maxSize];
            flag = true;
        }
        else
        {
            throw exception;
        }
    }
    catch(bad_alloc)
    {
        //cout << "Не удалось зааллоцировать память" << endl;
        myPointer = nullptr;
        flag = false;
        offset = 0;
        mySize = 0;
    }
}


char* Allocator::alloc(size_t size)
{
    //проверки на на корректность введенного размера
    if((offset + size > mySize) || (size <= 0))
    {
        return nullptr;
    }
    char* curPointer = myPointer + offset;
    offset += size;
    return curPointer;
}


void Allocator::reset()
{
    if (flag)
	{
		//сбрасываем смещение на 0
        offset = 0;
	}
}


Allocator::~Allocator()
{
    if(myPointer != nullptr)
    {
        delete[] myPointer;
    }
}