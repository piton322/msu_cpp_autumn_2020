#include <iostream>
#include <functional>
#include "parser.hpp"
#include <ctype.h>
#include <string>
using namespace std;


TokenParser::TokenParser() // функции не применяются
{
    startCallback = nullptr;
    endCallback = nullptr;
    digitCallback = nullptr;
    strCallback = nullptr;
}


// сразу задаем функции
TokenParser::TokenParser(const myPtr & start, 
                        const myPtr & end, 
                        const digitPtr & digit, 
                        const strPtr & str)
{
    startCallback = start;
    endCallback = end;
    digitCallback = digit;
    strCallback = str;
}


// задаем начальную функцию
void TokenParser::setStartCallback(const myPtr & start)
{
    startCallback = start;
}


// задаем конечную функцию
void TokenParser::setEndCallback(const myPtr & end)
{
    endCallback = end;
}


// задаем функцию для работы с числами
void TokenParser::setDigitCallback(const digitPtr & digit)
{
    digitCallback = digit;
}


// задаем функцию для работы со строками
void TokenParser::setStrCallback(const strPtr & str)
{
    strCallback = str;
}


void TokenParser::strOrDigitCallback(bool intFlag, const string & s, string & result)
{
    if (intFlag)
    {
        if(digitCallback != nullptr) // вызов функций только если они заданы
        {
            result += digitCallback(stoi(s));
        }
    }
    else
    {
        if(strCallback != nullptr)
        {
            result += strCallback(s);
        }
    }
}


string TokenParser::parse(const string & myText)
{
    string result = "";
    bool intFlag = true;
    bool spaceFlag = true;
    // если начальная функция задана, то вызываем ее
    if (startCallback != nullptr)
    {
        result += startCallback();
    }
    string s = "";
    for (const auto & i: myText)
    {
        if(isspace(i)) // все пробелы пропускаем
        {
            if(!spaceFlag)
            {
                strOrDigitCallback(intFlag, s, result);
            }
            s = "";
            intFlag = true;
            spaceFlag = true;
            continue;
        }
        else
        {
            spaceFlag = false;
            s += i;
            if(!isdigit(i))
            {
                intFlag = false;
            }
        }
    }
    // учитываем вывод последнего элемента, если в конце нет пробелов
    if (s != "")
    {
        strOrDigitCallback(intFlag, s, result);
    }
    // вызов конечной функции, если она задана
    if (endCallback != nullptr)
    {
        result += endCallback();
    }
    return result;
}
