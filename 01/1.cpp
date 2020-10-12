#include <iostream>
#include "1.hpp"
using namespace std;


Allocator::Allocator()
{
    myPointer = nullptr;
    flag = false;
}


void Allocator::makeAllocator(size_t maxSize)
{
    try
    {
        if (maxSize <= 0)
        {
            throw -1;
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
            throw -1;
        }
    }
    catch(...)
    {
        cout << "Не удалось зааллоцировать память" << endl;
    }
}


char* Allocator::alloc(size_t size)
{
    //проверки на на корректность введенного размера
    if((offset + size > mySize) || (size <= 0) || (mySize % size != 0))
    {
        return nullptr;
    }
    char* curPointer = myPointer + offset;
    offset += size;
    return curPointer;
}


void Allocator::reset()
{
    if (!flag)
		{
			cout << "Еще не было аллоцирования" << endl;
		}
    //сбрасываем смещение на 0
    offset = 0;
}


Allocator::~Allocator()
{
    if(myPointer != nullptr)
    {
        delete[] myPointer;
    }
}