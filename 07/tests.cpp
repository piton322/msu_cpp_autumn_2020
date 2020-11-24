#include <iostream>
#include "error.hpp"
#include "vect.hpp"
#include <string>
using namespace std;


void pushPopSizeCapacityTest() 
{
    Vect<int> vec;
    vec.push_back(1);
    vec.push_back(77);
    vec.push_back(322);
    assert(vec.size() == 3);
    assert(vec.capacity() == 3);
    vec.pop_back();
    assert(vec.size() == 2);
    assert(vec.capacity() == 3);
    assert(vec[0] == 1);
    assert(vec[1] == 77);
}

void emplaceTest()
{
    Vect<pair<string, string>> vec;
    vec.emplace_back("one", "two");
    assert(vec[0].first == "one");
    assert(vec[0].second == "two");
}

void clearAndEmptyTest()
{
    Vect<bool> vec;
    vec.push_back(true);
    vec.push_back(false);
    assert(vec.empty() == false);
    vec.clear();
    assert(vec.empty() == true);
}

void beginAndEndTest()
{
    Vect<int> vec;
    for (int i = 0; i < 5; i++)
    {
        vec.push_back(i);
    }
    int sum = 0;
    for (auto j = vec.begin(); j < vec.end(); j++)
    {
        sum += *j;
    }
    assert(sum == 10);
}

void rbeginAndRendTest()
{
    Vect<int> vec;
    for (int i = 0; i < 5; i++)
    {
        vec.push_back(i);
    }
    int sum = 10;
    for (auto j = vec.rbegin(); j != vec.rend(); j++)
    {
        sum -= *j;
    }
    assert(sum == 0);
}

void resizeTest()
{
    Vect<int> vec;
    for (int i = 0; i < 5; i++)
    {
        vec.push_back(i);
    }
    size_t temp = vec.capacity();
    vec.resize(1);
    assert(vec.size() == 1);
    assert(vec[0] == 0);
    assert(vec.capacity() == temp);
    vec.resize(555);
    assert(vec.size() == 555);
    assert(vec.capacity() == 1111);
}

void reserveTest()
{
    Vect<string> vec;
    vec.push_back("one");
    vec.push_back("two");
    vec.push_back("one");
    vec.push_back("five");
    size_t temp = vec.capacity();
    vec.reserve(temp - 1);
    assert(vec.size() == temp - 1);
    assert(vec.capacity() == temp);
    vec.reserve(temp + 10);
    assert(vec.size() == temp + 10);
    assert(vec.capacity() == temp + 10);
}

int main(int argc, char* argv[])
{
    pushPopSizeCapacityTest();
    emplaceTest();
    clearAndEmptyTest();
    beginAndEndTest();
    rbeginAndRendTest();
    resizeTest();
    reserveTest();
    cout << "Success!" << endl;
    return 0;
}