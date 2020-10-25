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
        Matrix(const size_t & row, const size_t & col);
        size_t getCol() const;
        size_t getRow() const;
        Arr operator [](const size_t  & n) const;
        Matrix & operator *=(int mul);
        friend ostream & operator <<(ostream &, const Matrix &);
        Matrix operator +(const Matrix & matSecond);
        bool operator ==(const Matrix& mat) const;
        bool operator !=(const Matrix& mat) const;
        ~Matrix();
};