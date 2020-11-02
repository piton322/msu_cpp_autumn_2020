#pragma once
#include <string>
#include <iostream>
using namespace std;


class BigInt
{
    private:
        char * myInt;
        size_t mySize;
        bool negFlag;
    public:
        BigInt();
        BigInt(size_t size);
        BigInt(int defInt);
        BigInt(const BigInt & myBigInt);
        BigInt(BigInt && myBigInt);
        BigInt(const string & str);
        size_t getSize() const;
        char * getStr() const;
        bool getFlag() const;
        void setFlag(bool fl);
        char & operator [](size_t i);
        const char & operator [](size_t i) const;
        friend ostream & operator <<(ostream &, const BigInt &);
        BigInt & operator =(const BigInt & myBigInt);
        BigInt & operator =(BigInt && myBigInt);
        BigInt operator +(const BigInt & myBigInt) const;
        BigInt operator +(int secInt) const;
        BigInt operator *(int secInt) const;
        BigInt operator -(int secInt) const;
        BigInt operator -() const;
        BigInt operator -(const BigInt & myBigInt) const;
        BigInt operator *(const BigInt & myBigInt) const;
        bool operator ==(const BigInt & myBigInt) const;
        bool operator !=(const BigInt & myBigInt) const;
        bool operator >(const BigInt & myBigInt) const;
        bool operator <(const BigInt & myBigInt) const;
        bool operator >=(const BigInt & myBigInt) const;
        bool operator <=(const BigInt & myBigInt) const;
        ~BigInt();
};