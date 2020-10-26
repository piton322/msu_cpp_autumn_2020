#pragma once
#include <iostream>
#include "arr.hpp"
using namespace std;


class Matrix
{
    private:
        int ** myMat;
        size_t myCol;
        size_t myRow;
    public:
        Matrix(const Matrix & mat);
        Matrix(size_t row, size_t col);
        size_t getCol() const;
        size_t getRow() const;
        Arr operator [](size_t);
        const Arr operator [](size_t) const;
        Matrix & operator *=(int mul);
        friend ostream & operator <<(ostream &, const Matrix &);
        Matrix operator +(const Matrix & matSecond) const;
        Matrix & operator =(const Matrix & matSecond);
        bool operator ==(const Matrix& mat) const;
        bool operator !=(const Matrix& mat) const;
        ~Matrix();
};