#pragma once
#include <iostream>
#include <string>
using namespace std;
using myPtr = string(*)();
using digitPtr = string(*)(int); // число передадим по значению
using strPtr = string(*)(const string &); // не будем изменять строку


class TokenParser
{
    private:
        myPtr startCallback;
        myPtr endCallback;
        strPtr strCallback;
        digitPtr digitCallback;
    public:
        TokenParser();
        TokenParser(const myPtr & start, 
                    const myPtr & end, 
                    const digitPtr & digit, 
                    const strPtr & str);
        string parse(const string & myText); // не будем изменять текст, с которым работаем
        void setStartCallback(const myPtr & start);
        void setDigitCallback(const digitPtr & digit);
        void setStrCallback(const strPtr & str);
        void setEndCallback(const myPtr & end);
};