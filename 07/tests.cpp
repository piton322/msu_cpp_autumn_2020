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

void fiveRuleTest()
{
    Vect<int> vec;
    for (int i = 0; i < 5; i++)
    {
        vec.push_back(i);
    }
    Vect<int> vec_sec = vec; // copy constructor
    assert(vec_sec.size() == vec.size());
    assert(vec_sec.capacity() == vec.capacity());
    for (int i = 0; i < 5; i++)
    {
        assert(vec[i] == vec_sec[i]);
    }

    Vect<int> vec_third = move(vec); // move constructor
    assert(vec_sec.size() == vec_third.size());
    assert(vec_sec.capacity() == vec_third.capacity());
    for (int i = 0; i < 5; i++)
    {
        assert(vec_third[i] == vec_sec[i]);
    }
    assert(vec.size() == 0);
    assert(vec.capacity() == 0);

    Vect<int> vec_fourth;
    vec_fourth = vec_sec; // copy assignment
    assert(vec_sec.size() == vec_fourth.size());
    assert(vec_sec.capacity() == vec_fourth.capacity());
    for (int i = 0; i < 5; i++)
    {
        assert(vec_fourth[i] == vec_sec[i]);
    }

    Vect<int> vec_fifth;
    vec_fifth = move(vec_fourth); // move assignment
    assert(vec_sec.size() == vec_fifth.size());
    assert(vec_sec.capacity() == vec_fifth.capacity());
    for (int i = 0; i < 5; i++)
    {
        assert(vec_fifth[i] == vec_sec[i]);
    }
    assert(vec_fourth.size() == 0);
    assert(vec_fourth.capacity() == 0);
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
    fiveRuleTest();
    cout << "Success!" << endl;
    return 0;
}