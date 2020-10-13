#include <iostream>
#include "allocator.hpp"
using namespace std;


struct myStruct
{
    int x, y, z;
};
typedef struct myStruct exampleStruct;


void defaultWorkTest()
{
    Allocator allocator;
    allocator.makeAllocator(sizeof(exampleStruct) * 10);
    for (auto i = 0; i < 10; i++)
    {
        exampleStruct* arr = (exampleStruct*) allocator.alloc(sizeof(exampleStruct));
        arr->x = arr->y = arr->z = i;
    }
    // после действий выше отступ должен дойти до всего размера
    if ((allocator.offset != sizeof(exampleStruct) * 10) ||
        (allocator.mySize != sizeof(exampleStruct) * 10) ||
        (allocator.myPointer == nullptr))
    {
        throw -1;
    }
    allocator.reset();
    if (allocator.offset != 0)
    {
        throw -1;
    }
    // если все условия выполнись, то все хорошо
}


void negativeTest()
{
    Allocator allocatorFirst;
    allocatorFirst.makeAllocator(sizeof(char) * -100);
    if (allocatorFirst.myPointer != nullptr)
    {
        throw -1;
    }
    // если ничего не выделилось, то все верно
}


void takeMoreThanExist()
{
    Allocator allocatorSecond;
    allocatorSecond.makeAllocator(sizeof(char) * 100);
    char * a;
    char * aRuin;
    a = allocatorSecond.alloc(sizeof(char) * 100);
    aRuin = allocatorSecond.alloc(sizeof(char) * 1);
    if (aRuin != nullptr)
    {
        throw -1;
    }
    // иначе все хорошо, не можем получить больше, чем выделили
}


void resetBeforeMake()
{
    Allocator allocatorFourth;
    allocatorFourth.reset();
    if (allocatorFourth.flag)
    {
        throw -1;
    }
    // иначе не сделали сброс, пока не было выделения памяти
}


void makeAfterMake()
{
    char * aF;
    char * aS;
    Allocator allocatorThird;
    allocatorThird.makeAllocator(sizeof(char) * 8);
    aF = allocatorThird.alloc(sizeof(char) * 4);
    aS = allocatorThird.alloc(sizeof(char) * 4);
    *aF = 'l';
    *aS = 'o';
    allocatorThird.makeAllocator(sizeof(char) * 16);
    if (allocatorThird.myPointer != nullptr)
    {
        throw -1;
    }
}


void enterAfterReset()
{
    char * aF;
    char * aS;
    Allocator allocatorLast;
    allocatorLast.makeAllocator(sizeof(char) * 8);
    aF = allocatorLast.alloc(sizeof(char) * 4);
    aS = allocatorLast.alloc(sizeof(char) * 4);
    *aF = 'l';
    *aS = 'o';
    allocatorLast.reset();
    char * aFirst;
    char * aSecond;
    aFirst = allocatorLast.alloc(sizeof(char)*4);
    aSecond = allocatorLast.alloc(sizeof(char)*4);
    if ((aFirst != nullptr) and (aSecond != nullptr))
    {
        *aFirst = '1';
        *aSecond = '2';
    }
    else
    {
	throw -1;
    }
}
int main(int argc, char* argv[])
{
    defaultWorkTest();
    negativeTest();
    takeMoreThanExist();
    resetBeforeMake();
    makeAfterMake();
    enterAfterReset();
    cout << "Success!" << endl;
    return 0;
}
