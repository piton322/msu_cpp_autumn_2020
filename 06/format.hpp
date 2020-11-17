#pragma once
#include "error.hpp"
#include <stdlib.h>
#include <string>
#include <sstream>
using namespace std;


static int numberParameters = 0; // число параметров


template <class T>
string workWithFormat(const string & str, const T & first)
{
    stringstream res;
    string context; // здесь будет то, что внутри {}
    bool flag = false; // флаг - находимся внутри контекста или нет
    int curPar = numberParameters;
    for (const char & i: str)
    {
        if (i == '{')
        {
            if (flag) // если мы уже внутри контекста, то ошибка
            {
                throw Error::BracketsError;
            }
            flag = true;
            continue;
        }
        if (i == '}')
        {
            if(!flag) // если мы уже вышли из контекста, то ошибка
            {
                throw Error::BracketsError;
            }
            if (context.empty()) // если в скобках ничего нет
            {
                throw Error::BracketsError;
            }
            try
            {
                curPar = stoul(context);
            }
            catch (const logic_error & e)
            {
                throw Error::ParameterError;
            }
            if (curPar == numberParameters)
            {
                res << first;
            }
            else
            {
                string s = "{" + context + "}";
                res << s;
            }
            context = "";
            flag = false;
            continue;
        }
        if(flag) // находимся внутри контекста
        {
            if(isdigit(i))
            {
                context += i;
            }
            else
            {
                throw Error::ParameterError;
            }
        }
        else // вышли из контекста
        {
            res << i;
        }       
    }
    numberParameters++;
    return res.str();
}


template <class T>
string format(const string & str, const T & first)
{
    string res = workWithFormat(str, first);
    numberParameters = 0;
    return res;
}


template <class T, class ... ArgsT>
string format(const string & str, const T & first, const ArgsT & ... args)
{
    string res = workWithFormat(str, first);
    return format(res, args ...);
};