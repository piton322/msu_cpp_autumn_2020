#include <iostream>
#include "arr.hpp"
using namespace std;


Arr::Arr(int * mas, size_t n): myMas(mas), myN(n){};


int & Arr::operator [](size_t n)
{
    if (n >= myN)
    {
        throw out_of_range("Index is out of dimension!");
    }
    return myMas[n];
}
const int & Arr::operator [](size_t n) const
{
    if (n >= myN)
    {
        throw out_of_range("Index is out of dimension!");
    }
    return myMas[n];
}