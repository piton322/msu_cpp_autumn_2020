#include "threadpool.hpp"
#include <iostream>
#include "error.hpp"
#include <string>


struct A {};
void foo(const A&) {}


void defaultWorkTest()
{
    ThreadPool pool(8);
    auto result_first = pool.exec(foo, A());
    result_first.get();
    auto result_second = pool.exec([]() { return 1; });
    assert(result_second.get() == 1);
}


void someFuncTest()
{
    ThreadPool pool(6);
    int first_number = 322;
    auto goal_first = [first_number](int number) 
    { 
        return first_number - number; 
    };
    auto result_first = pool.exec(goal_first, 322);
    assert(result_first.get() == 0);
    int second_number = 777;
    int mul = 2;
    int add = -1554;
    auto goal_second = [second_number, mul, add]() 
    { 
        return second_number * mul + add; 
    };
    auto result_second = pool.exec(goal_second);
    assert(result_second.get() == 0);
}


string someFunc(string str_first, string str_second)
{
    return str_first + str_second;
}


void fullPoolTest()
{
    ThreadPool pool(3);
    for (int i = 0; i < 3; i++)
    {
        auto result = pool.exec(someFunc, "a", "b");
        assert(result.get() == "ab");
    }
}


int main(int argc, char const *argv[])
{
    defaultWorkTest();
    someFuncTest();
    fullPoolTest();
    cout << "Success!" << endl;
    return 0;
}