#include <iostream>
#include "1.hpp"
using namespace std;


struct myStruct
{
    int x, y, z;
};

typedef struct myStruct exampleStruct;


int main(int argc, char* argv[])
{
    // Тест 1 - покажем, что все нормально при обычной работе
    cout << "Тест 1, нормальная работа, выводим отступы:" << endl;
    Allocator allocator;
    allocator.makeAllocator(sizeof(exampleStruct) * 10);
    cout << allocator.offset << " " << &allocator.myPointer << " " << allocator.mySize << endl;
    for (auto i = 0; i < 10; i++)
    {
        exampleStruct* arr = (exampleStruct*) allocator.alloc(sizeof(exampleStruct));
        cout << allocator.offset << endl;
        arr->x = arr->y = arr->z = i;
    }
    allocator.reset();
    cout << "Отступ после reset" << endl;
    cout << allocator.offset << endl;


    // Тест 2 - размер <= 0
    cout << "Тест 2:" << endl;
    Allocator allocatorFirst;
    cout << "allocatorFirst:" << endl;
    allocatorFirst.makeAllocator(sizeof(char) * -100);
    

    // Тест 3 - пытаемся получить больше, чем выделили
    cout << "Тест 3:" << endl;
    Allocator allocatorSecond;
    cout << "allocatorSecond:" << endl;
    allocatorSecond.makeAllocator(sizeof(char) * 100);
    char * a;
    char * aRuin;
    a = allocatorSecond.alloc(sizeof(char) * 100);
    cout << "Занято: " << allocatorSecond.offset << endl;
    aRuin = allocatorSecond.alloc(sizeof(char) * 1);
    if (aRuin == nullptr)
    {
        cout << "Не можем получить больше, чем выделили" << endl;
    }

    // Тест 4 - два раза makeAllocator
    cout << "Тест 4:" << endl;
    Allocator allocatorThird;
    cout << "allocatorThird:" << endl;
    allocatorThird.makeAllocator(sizeof(char) * 16);
    allocatorThird.makeAllocator(sizeof(char) * 16);


    // Тест 5 - reset до makeAllocator
    cout << "Тест 5:" << endl;
    Allocator allocatorFourth;
    cout << "allocatorFourth:" << endl;
    allocatorFourth.reset();


    // Тест 6 - ввод после reset (используем данные из теста 1)
    cout << "Тест 6:" << endl;
    char * aFirst;
    char * aSecond;
    aFirst = allocator.alloc(sizeof(char)*4);
    aSecond = allocator.alloc(sizeof(char)*4);
	if ((aFirst != nullptr) and (aSecond != nullptr))
    {
        *aFirst = '1';
        *aSecond = '2';
        cout << *aFirst << ' ' << *aSecond << " offset = " << allocator.offset << endl;
    }
	else
	{
		cout<<"error with reset "<<endl;
	}
    return 0;
}