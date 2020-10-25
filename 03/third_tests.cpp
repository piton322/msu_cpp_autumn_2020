#include <iostream>
#include "matrix.hpp"
#include "arr.hpp"
using namespace std;


void createAndGetTest()
{
    const size_t rows = 5;
    const size_t cols = 3;
    Matrix mFirst(rows, cols);
    assert(mFirst.getRow() == 5);
    assert(mFirst.getCol() == 3);
}


void elementAndOutTest()
{
    const size_t rows = 3;
    const size_t cols = 3;
    Matrix mSecond(rows, cols);
    for (auto i = 0; i < mSecond.getRow(); i++)
    {
        for(auto j = 0; j < mSecond.getCol(); j++)
        {
            mSecond[i][j] = 4;
        }
    }
    assert(mSecond[2][1] == 4);
    mSecond[2][1] = 77;
    assert(mSecond[2][1] == 77);
    cout << mSecond;
}


void mulTest()
{
    const size_t rows = 3;
    const size_t cols = 3;
    Matrix mThird(rows, cols);
    for (auto i = 0; i < mThird.getRow(); i++)
    {
        for(auto j = 0; j < mThird.getCol(); j++)
        {
            mThird[i][j] = 4;
        }
    }
    mThird *= 2;
    for (auto i = 0; i < mThird.getRow(); i++)
    {
        for(auto j = 0; j < mThird.getCol(); j++)
        {
            assert(mThird[i][j] == 8);
        }
    }
}


void equalTest()
{
    const size_t rows = 2;
    const size_t cols = 4;
    Matrix mFourth(rows, cols);
    for (auto i = 0; i < mFourth.getRow(); i++)
    {
        for(auto j = 0; j < mFourth.getCol(); j++)
        {
            mFourth[i][j] = 6;
        }
    }
    Matrix mFifth(mFourth);
    assert (mFifth == mFourth);
    mFifth[1][1] = 2;
    assert (mFifth != mFourth);
}


void sumTest()
{
    const size_t rows = 2;
    const size_t cols = 4;
    Matrix mSixth(rows, cols);
    for (auto i = 0; i < mSixth.getRow(); i++)
    {
        for(auto j = 0; j < mSixth.getCol(); j++)
        {
            mSixth[i][j] = 6;
        }
    }
    Matrix mSeventh(mSixth);
    Matrix mSum = mSixth + mSeventh;
    for (auto i = 0; i < mSum.getRow(); i++)
    {
        for(auto j = 0; j < mSum.getCol(); j++)
        {
            assert(mSum[i][j] == 12);
        }
    }
}


void rangeTest()
{
    const size_t rows = 2;
    const size_t cols = 4;
    Matrix mEighth(rows, cols);
    try
    {
        mEighth[3][2] = 2;
    }
    catch(out_of_range)
    {
        // ошибка при выходе за границу
    }
    try
    {
        mEighth[2][5] = 6;
    }
    catch(out_of_range)
    {
        // ошибка при выходе за границу
    }
}
int main(int argc, char* argv[])
{
    createAndGetTest();
    elementAndOutTest();
    mulTest();
    equalTest();
    sumTest();
    rangeTest();
    cout << "Succes!" << endl;
    return 0;
}