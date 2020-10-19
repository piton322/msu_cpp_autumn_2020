#include <iostream>
#include <string>
#include "parser.hpp"
using namespace std;


string myStart()
{
    return "Начало ";
}


string myEnd()
{
    return " Конец";
}


string myDigit(int digit)
{
    return to_string(digit);
}


string myStr(const string & str)
{
    return str;
}   


string myStrSecond(const string & str)
{
    return str + str;
}

void defaultWorkTest()
{
    TokenParser parserFirst;
    parserFirst.setStartCallback(myStart);
    parserFirst.setEndCallback(myEnd);
    parserFirst.setDigitCallback(myDigit);
    parserFirst.setStrCallback(myStr);
    string s = "hoho 12gsd   \t\n123  \r   krk";
    if (parserFirst.parse(s) != "Начало hoho12gsd123krk Конец")
    {
        throw -1;
    }
    // иначе все прошло успешно
}


void emptyAndConstuctTest()
{
    TokenParser parserSecond = TokenParser(myStart, myEnd, myDigit, myStr);
    string s = "   ";
   if (parserSecond.parse(s) != "Начало  Конец")
   {
       throw -1;
   }
   // иначе все прошло успешно
}


void parseBeforeSetTest()
{
    TokenParser parserThird;
    string s = "123 aa  322 b";
    if (parserThird.parse(s) != "")
    {
        throw -1;
    }
    // иначе все прошло успешно
}


void resetTest()
{
    TokenParser parserLast = TokenParser(myStart, myEnd, myDigit, myStr);
    string s = " dhhg  23 \t 42 \n rw42fsd 33r 0.04 2";
    parserLast.setStrCallback(myStrSecond);
    if (parserLast.parse(s) != "Начало dhhgdhhg2342rw42fsdrw42fsd33r33r0.040.042 Конец")
    {
        throw -1;
    }
    // иначе все прошло успешно
}


int main(int argc, char* argv[])
{
    defaultWorkTest();
    emptyAndConstuctTest();
    parseBeforeSetTest();
    resetTest();
    cout << "Success!" << endl;
    return 0;
}