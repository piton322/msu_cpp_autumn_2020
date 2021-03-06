#include <iostream>
#include "arr.hpp"
#include "matrix.hpp"
using namespace std;


Matrix::Matrix(const Matrix & mat): myCol(mat.getCol()), myRow(mat.getRow())
{
    myMat = new int * [mat.getRow()];
    for (auto i = 0; i < mat.getRow(); i++)
    {
        myMat[i] = new int [mat.getCol()];
        for (auto j = 0; j < mat.getCol(); j++)
        {
            myMat[i][j] = mat.myMat[i][j];
        }
    }
}


Matrix::Matrix(size_t row, size_t col): myCol(col), myRow(row)
{
    myMat = new int * [row];
    for (auto i = 0; i < row; i++)
    {
        myMat[i] = new int [col];
    }
}


size_t Matrix::getCol() const
{
    return myCol;
}


size_t Matrix::getRow() const
{
    return myRow;
}


Arr Matrix::operator[](size_t n)
{
    if (n >= myRow)
    {
        throw out_of_range("Dimension error");
    }
    return Arr(myMat[n], myCol);
}


const Arr Matrix::operator[](size_t n) const
{
    if (n >= myRow)
    {
        throw out_of_range("Dimension error");
    }
    return Arr(myMat[n], myCol);
}


Matrix & Matrix::operator *=(int mul)
{
    for (auto i = 0; i < myRow; i++)
    {
        for(auto j = 0; j < myCol; j++)
        {
            myMat[i][j] *= mul;
        }
    }
    return * this;
}


ostream & operator <<(ostream & myOut, const Matrix & mat)
{
    for (auto i = 0; i < mat.getRow(); i++)
    {
        for(auto j = 0; j < mat.getCol(); j++)
        {
            myOut << mat[i][j] << " ";
        }
        myOut << endl;
    }
    return myOut;
}


Matrix Matrix::operator +(const Matrix & matSecond) const
{
    if ((myCol != matSecond.getCol()) 
        || (myRow != matSecond.getRow()))
    {
        throw out_of_range("Different dimensions");
    }    
    Matrix matFirst = Matrix(myRow, myCol);
    for (auto i = 0; i < myRow; i++)
    {
        for(auto j = 0; j < myCol; j++)
        {
            matFirst[i][j] = myMat[i][j] + matSecond[i][j];
        }
    }
    return matFirst;
}


Matrix & Matrix::operator =(const Matrix & matSecond)
{
    if ((myCol != matSecond.getCol()) 
        || (myRow != matSecond.getRow()))
    {
        throw out_of_range("Different dimensions");
    }
    myCol = matSecond.getCol();
    myRow = matSecond.getRow();
    for (auto i = 0; i < myRow; i++)
    {
        for(auto j = 0; j < myCol; j++)
        {
            myMat[i][j] = matSecond[i][j];
        }
    }
    return * this;
}


bool Matrix::operator ==(const Matrix& mat) const
{
    if ((myCol != mat.getCol()) || (myRow != mat.getRow()))
    {
        return false;
    }
    else
    {
        for (auto i = 0; i < myRow; i++)
        {
            for(auto j = 0; j < myCol; j++)
            {
                if (myMat[i][j] != mat[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }
}


bool Matrix::operator !=(const Matrix& mat) const
{
    return !(* this == mat);
}


Matrix::~Matrix()
{
    for (auto i = 0; i < myRow; i++)
    {
        delete[] myMat[i];
    }
    delete[] myMat;
}
