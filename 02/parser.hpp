#pragma once
#include <iostream>
#include <string>
#include <functional>
using namespace std;
using myPtr = function<string ()>;
using digitPtr = function<string (int)>; // число передадим по значению
using strPtr = function<string (const string &)>; // не будем изменять строку


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
        void strOrDigitCallback(bool intFlag, const string & s, string & result);
        void setEndCallback(const myPtr & end);
};