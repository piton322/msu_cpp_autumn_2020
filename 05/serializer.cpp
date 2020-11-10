#include <iostream>
#include "serializer.hpp"
using namespace std;


void Serializer::parameterToStream(bool parameter)
{
    myOut << boolalpha << parameter; // делаем строку true или false
}


void Serializer::parameterToStream(uint64_t parameter)
{
    myOut << parameter;
}