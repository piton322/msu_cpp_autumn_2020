#include <iostream>
#include <string>
#include "bigint.hpp"
using namespace std;

void createAndGetAndOutTest()
{
    string s = "-322";
    BigInt num(s);
    assert(num.getFlag() == true);
    assert(num.getSize() == 3);
    cout << num;
}


void copyAndMoveTest()
{
    BigInt numFirst = 4444;
    BigInt numSecond = numFirst;
    string s = "4444";
    for (int i = 0; i < numSecond.getSize(); i++)
    {
        assert(numSecond[i] == s[i]);
    }
    BigInt numThird = move(numFirst);
    assert(numFirst.getStr() == nullptr);
    for (int i = 0; i < numThird.getSize(); i++)
    {
        assert(numThird[i] == s[i]);
    }
    BigInt numFourth;
    numFourth = move(numThird);
    assert(numThird.getStr() == nullptr);
    for (int i = 0; i < numFourth.getSize(); i++)
    {
        assert(numFourth[i] == s[i]);
    }
}


void subOneTest()
{
    BigInt num(-3333);
    assert((-num).getFlag() == false);
    for (int i = 0; i < (-num).getSize(); i++)
    {
        assert((-num)[i] == '3');
    }
}


void addAndSubTest()
{
    BigInt num = BigInt("322666");
    BigInt numSec(2222);
    string s = "320444";
    string sSec = "1";
    BigInt x;
    x = num - numSec;
    int i = 0;
    while(x[i] == '0')
    {
        i++;
    }
    for (int j = i; j < x.getSize(); j++)
    {
        assert(x[j] == s[j-i]);
    }
    BigInt y = x + 1;
    x = -x + x * 2 - y;
    i = 0;
    while(x[i] == '0')
    {
        i++;
    }
    for (int j = i; j < x.getSize(); j++)
    {
        assert(x[j] == sSec[j-i]);
    }
}


void mulHardTest()
{
    BigInt numFirst("3423234243243232423324324323243242342342");
    BigInt numSecond("4212422421221");
    BigInt numThird("42412243");
    string s = "145187042570353081643510111008202942331298093106";
    string sSec = "935081777511138";
    int i = 0;
    numFirst = numFirst * numThird;
    while(numFirst[i] == '0')
    {
        i++;
    }
    for (int j = i; j < numFirst.getSize(); j++)
    {
        assert(numFirst[j] == s[j-i]);
    }
    i = 0;
    numFirst = (numSecond - 342342342) * (-222);
    while(numFirst[i] == '0')
    {
        i++;
    }
    for (int j = i; j < numFirst.getSize(); j++)
    {
        assert(numFirst[j] == sSec[j-i]);
    }
    assert(numFirst.getFlag() == true);
}


void compareTest()
{
    BigInt numFirst("122");
    BigInt numSecond("-2223");
    BigInt numThird("55");
    BigInt numFourth("-55");
    assert((numFirst > numSecond) == true);
    assert((numSecond < numThird) == true);
    assert((numThird == (-numFourth)) == true);
    assert((numFourth != numSecond) == true);
}


int main(int argc, char* argv[])
{
    createAndGetAndOutTest();
    copyAndMoveTest();
    subOneTest();
    addAndSubTest();
    mulHardTest();
    compareTest();
    cout << "Success!" << endl;
    return 0;
}