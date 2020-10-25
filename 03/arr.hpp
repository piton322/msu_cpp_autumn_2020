#pragma once


class Arr
{
    private:
        int * myMas;
        size_t myN;
    public:
        Arr(int * mas, size_t n);
        int & operator [](size_t n) const;
};