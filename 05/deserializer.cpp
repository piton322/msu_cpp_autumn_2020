#include <iostream>
#include "error.hpp"
#include "deserializer.hpp"
#include <string>
using namespace std;


void Deserializer::parameterFromStream(bool & parameter)
{
    string text;
    myIn >> text;
    if (text == "true")
        parameter = true;
    else if (text == "false")
        parameter = false;
    else
        throw Error::CorruptedArchive;
}


void Deserializer::parameterFromStream(uint64_t & parameter)
{
    string text;
    myIn >> text;
    if (text[0] == '-')
    {
        throw Error::CorruptedArchive;
    }
    try
    {
        parameter = stoull(text);
    }
    catch(exception & e)
    {
        throw Error::CorruptedArchive;
    }
}