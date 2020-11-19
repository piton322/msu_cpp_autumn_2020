#include <iostream>
#include <string>
#include <sstream>
#include "error.hpp"
#include "format.hpp"
using namespace std;


void defaultWorkTest()
{
    auto text = format("{1} + {1} = {0}", 2, "one");
    assert(text == "one + one = 2");
}


void secDefTest()
{
    auto text = format("Домашнее задание номер {0}, тест {1}, строка {2}", 6, 2, 18);
    assert(text == "Домашнее задание номер 6, тест 2, строка 18");
}


void lessTest()
{
    try
    {
        auto text = format("{1} + {2} + {3} / {0}", 1, 2);
    }
    catch(const Error & err)
    {
        assert(err == Error::ParameterError);
    }
}


void largerTest()
{
    try
    {
        auto text = format("{1} + {2} + {3} / {0}", 1, 2, 3, 4, 322, 777);
    }
    catch(const Error & err)
    {
        assert(err == Error::ParameterError);
    }
}


void bracketsErrorTest()
{
    try
    {
        auto text = format("{}", 1);
    }
    catch(const Error & err)
    {
        assert(err == Error::BracketsError);
    }
}


void secBracketsErrorTest()
{
    try
    {
        auto text = format("{0{}", 1);
    }
    catch(const Error & err)
    {
        assert(err == Error::BracketsError);
    }
}


void notNumberTest()
{
    try
    {
        auto text = format("{0asd}", 1);
    }
    catch(const Error & err)
    {
        assert(err == Error::ParameterError);
    }
}


void extraTestFirst()
{
    try
    {
        auto text = format("{2}+{2} = {0}", 2, "one");
    }
    catch(const Error & err)
    {
        assert(err == Error::ParameterError);
    }
}


void extraTestSecond()
{
    try
    {
        auto text = format("{1}+{1} = {0", 2, "one");
    }
    catch(const Error & err)
    {
        assert(err == Error::BracketsError);
    }
}


int main()
{
    defaultWorkTest();
    secDefTest();
    lessTest();
    largerTest();
    bracketsErrorTest();
    secBracketsErrorTest();
    notNumberTest();
    extraTestFirst();
    extraTestSecond();
    cout << "Success!" << endl;
    return 0;
}