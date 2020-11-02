#include <iostream>
#include "bigint.hpp"
#include <string>
#include <stdlib.h>
using namespace std;


BigInt::BigInt(): myInt(nullptr), mySize(0), negFlag(false){}


BigInt::BigInt(int defInt)
{
    string str = to_string(defInt);
    if (str[0] == '-')
    {
        negFlag = true;
        myInt = strdup(&str.c_str()[1]);
        mySize = str.length() - 1;
    }
    else
    {
        negFlag = false;
        myInt = strdup(str.c_str());
        mySize = str.length();
    }
}

BigInt::BigInt(size_t size): mySize(size), negFlag(false)
{
    myInt = new char[size];
    for (int i = 0; i < size; i++)
    {
        myInt[i] = '0';
    }
}


BigInt::BigInt(const BigInt & myBigInt): mySize(myBigInt.getSize()), negFlag(myBigInt.getFlag())
{
    myInt = new char[myBigInt.getSize()];
    for (int i = 0; i < myBigInt.getSize(); i++)
    {
        myInt[i] = myBigInt[i];
    }
}

BigInt::BigInt(BigInt && myBigInt): mySize(move(myBigInt.getSize())), negFlag(move(myBigInt.getFlag()))
{
    myInt = myBigInt.getStr();
    myBigInt.myInt = nullptr;
    myBigInt.mySize = 0;
}
BigInt::BigInt(const string & str)
{
    if (str[0] == '-')
    {
        negFlag = true;
        myInt = strdup(&str.c_str()[1]);
        mySize = str.length() - 1;
    }
    else
    {
        negFlag = false;
        myInt = strdup(str.c_str());
        mySize = str.length();
    }
}


char * BigInt::getStr() const
{
    return myInt;
}


size_t BigInt::getSize() const
{
    return mySize;
}


bool BigInt::getFlag() const
{
    return negFlag;
}


void BigInt::setFlag(bool fl)
{
    negFlag = fl;
}

ostream & operator <<(ostream & myOut, const BigInt & myBigInt)
{
    if(myBigInt.getFlag())
    {
        myOut << "-";
    }
    int i = 0;
    if (myBigInt.getSize() != 1)
    {
        while(myBigInt[i] == '0')
        {
            i++;
        }
    }
    for (int j = i; j < myBigInt.getSize(); j++)
    {
        myOut << myBigInt[j];
    }
    myOut << endl;
    return myOut;
}

char & BigInt::operator [](size_t i)
{
    if (i >= mySize)
    {
        throw out_of_range("Different sizes");
    }
    return myInt[i];
}


const char & BigInt::operator [](size_t i) const
{
    if (i >= mySize)
    {
        throw out_of_range("Different sizes");
    }
    return myInt[i];
}


BigInt BigInt::operator +(const BigInt & myBigInt) const
{
    int first;
    int second;
    size_t limitFirst = 0;
    size_t limitSecond = 0;
    int addition = 0;
    if(negFlag & !myBigInt.getFlag())
    {
        return *this - (-myBigInt);
    }
    if (!negFlag & myBigInt.getFlag())
    {
        return myBigInt - (-*this);
    }
    string str (max(myBigInt.getSize(), mySize) + 1, '0');
    BigInt result = BigInt(str);
    limitFirst = result.getSize() - mySize;
    limitSecond = result.getSize() - myBigInt.getSize();
    for(int i = result.getSize() - 1; i >= 1; i--)
    {
        if(i >= limitFirst)
        {
            first = myInt[i-limitFirst] - '0';
        }
        else
        {
            first = 0;
        }
        if(i >= limitSecond)
        {
            second = myBigInt[i-limitSecond] - '0';
        }
        else
        {
            second = 0;
        }
        first = first + second;
        result[i] = (first + addition) % 10 + '0';
        if (i > 1)
        {
            addition = first / 10;
        }
        else
        {
            result[0] = (first + addition) / 10 + '0';
        }
    }
    if(negFlag == true)
    {
        result.setFlag(true);
    }
    else
    {
        result.setFlag(false);
    }
    return result;
}


BigInt BigInt::operator +(int secInt) const
{
    BigInt help = BigInt(to_string(secInt));
    return *this + help;
}


BigInt BigInt::operator *(int secInt) const
{
    BigInt help = BigInt(to_string(secInt));
    return *this * help;
}


BigInt BigInt::operator -(int secInt) const
{
    BigInt help = BigInt(to_string(secInt));
    return *this - help;
}


BigInt BigInt::operator -() const
{
    BigInt result = BigInt(*this);
    result.setFlag(!result.getFlag());
    return result;
}


BigInt BigInt::operator -(const BigInt & myBigInt) const
{
    int first;
    int second;
    size_t limitFirst = 0;
    size_t limitSecond = 0;
    int sub = 0;
    if(negFlag & myBigInt.getFlag())
    {
        return (-myBigInt) - (-*this);
    }
    if(negFlag & !myBigInt.getFlag())
    {
        return -(-*this + myBigInt);
    }
    if(!negFlag & myBigInt.getFlag())
    {
        return *this + (-myBigInt);
    }
    if(!negFlag & !myBigInt.getFlag())
    {
        if(*this < myBigInt)
        {
            return -(myBigInt - *this);
        }
    }
    // обычный случай *this >= myBigInt >= 0
    string str (max(myBigInt.getSize(), mySize), '0');
    BigInt result = BigInt(str);
    limitFirst = result.getSize() - mySize;
    limitSecond = result.getSize() - myBigInt.getSize();
    for(int i = result.getSize() - 1; i >= 0; i--)
    {
        if(i >= limitFirst)
        {
            first = myInt[i-limitFirst] - '0';
        }
        else
        {
            first = 0;
        }
        if(i >= limitSecond)
        {
            second = myBigInt[i-limitSecond] - '0';
        }
        else
        {
            second = 0;
        }
        if(first - sub >= second)
        {
            first = first - sub - second;
            sub = 0;
        }
        else
        {
            first = first + 10 - sub - second;
            sub = 1;
        }
        result[i] = first + '0';
    }
    return result;
}


BigInt BigInt::operator *(const BigInt & myBigInt) const
{
    int first = 0;
    int second = 0;
    int c = 0;
    char t;
    string str (myBigInt.getSize() + mySize, '0');
    BigInt result = BigInt(str);
    int * res = new int [myBigInt.getSize() + mySize];
    for (int i = 0; i < myBigInt.getSize() + mySize; i++)
    {
        res[i] = 0;
    }
    for (int i = 0; i < mySize; i++)
    {
        c = 0;
        for (int j = 0; j < myBigInt.getSize(); j++)
        {
            first = myInt[mySize - i - 1] - '0';
            second = myBigInt[myBigInt.getSize() - j - 1] - '0';
            res[myBigInt.getSize() + mySize - (i + j) - 1] += c + first * second;
            c = res[myBigInt.getSize() + mySize - (i + j) - 1] / 10;
            res[myBigInt.getSize() + mySize - (i + j) - 1] %= 10;
        }
        res[myBigInt.getSize() + mySize - (i + myBigInt.getSize()) - 1] += c;
    }
    for (int i = 0; i < myBigInt.getSize() + mySize; i++)
    {
        t = res[i] + '0';
        result[i] = t;
    }
    if (negFlag ^ myBigInt.getFlag())
    {
        result.setFlag(true);
    }
    else
    {
        result.setFlag(false);
    }
    return result;
}


BigInt & BigInt::operator =(const BigInt & myBigInt)
{
    if(this == &myBigInt)
    {
        return *this;
    }
    mySize = myBigInt.getSize();
    char * tmp = new char[mySize];
    delete[] myInt;
    myInt = tmp;
    for (int i = 0; i < mySize; i++)
    {
        myInt[i] = myBigInt[i];
    }
    return * this;
}


BigInt & BigInt::operator =(BigInt && myBigInt)
{
    if(this == &myBigInt)
    {
        return *this;
    }
    mySize = move(myBigInt.getSize());
    myInt = myBigInt.getStr();
    negFlag = move(myBigInt.getFlag());
    myBigInt.myInt = nullptr;
    myBigInt.mySize = 0;
    return * this;
}


bool BigInt::operator ==(const BigInt & myBigInt) const
{
    if(mySize != myBigInt.getSize())
    {
        return false;
    }
    for (int i = 0; i < mySize; i++)
    {
        if(myInt[i] != myBigInt[i])
        {
            return false;
        }
    }
    return true;
}


bool BigInt::operator !=(const BigInt & myBigInt) const
{
    return !(*this == myBigInt);
}


bool BigInt::operator <(const BigInt & myBigInt) const
{
    if(*this == myBigInt)
    {
        return false;
    }
    if(negFlag)
    {
        if(myBigInt.getFlag())
        {
            return ((-myBigInt) < (-*this));
        }
        else
        {
            return true;
        }
    }
    else if(myBigInt.getFlag())
    {
        return false;
    }
    else
    {
        if(mySize != myBigInt.getSize())
        {
            return mySize < myBigInt.getSize();
        }
        else
        {
            for (int i = mySize - 1; i >= 0; --i) 
            {
                if (myInt[i] != myBigInt[i])
                { 
                    return myInt[i] < myBigInt[i];
                }
            }
            return false;
        }
    }
}


bool BigInt::operator >=(const BigInt & myBigInt) const
{
    return !(*this < myBigInt);
}


bool BigInt::operator <=(const BigInt & myBigInt) const
{
    return ((*this < myBigInt) || (*this == myBigInt));
}


bool BigInt::operator >(const BigInt & myBigInt) const
{
    return !(*this <= myBigInt);
}


BigInt::~BigInt()
{
    if(myInt != nullptr)
    {
        delete[] myInt;
    }
}