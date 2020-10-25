#include <iostream>
#include "arr.hpp"
using namespace std;


Arr::Arr(int * mas, size_t n) : myN(n)
{
    this->myMas = mas;
}

int& Arr::operator [](size_t n) const
{
    if (n < myN)
    {
        return myMas[n];
    }
    else
    {
        throw out_of_range("Index is out of dimension!");
    }
}