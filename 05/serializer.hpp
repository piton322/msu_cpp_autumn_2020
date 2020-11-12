#pragma once
#include <iostream>
#include "error.hpp"
using namespace std;


class Serializer
{
public: // паблик секция из подсказки к домашней работе
    explicit Serializer(ostream & out): myOut(out){}

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class ... ArgsT>
    Error operator()(ArgsT && ... args)
    {
        return process(forward<ArgsT>(args)...);
    }
    
private:
    static constexpr char Separator = ' ';  // расчитан на этапе компиляции
    ostream & myOut;

    void parameterToStream(bool parameter);
    void parameterToStream(uint64_t parameter);

    template <class T>
    void parameterToStream(T) // не bool и не uint64_t
    {
        throw Error::CorruptedArchive;
    }

    template<class T, class ... ArgsT>
    Error process(T && curParameter, ArgsT && ... args)
    {
        try
        {
            parameterToStream(curParameter);
        }
        catch(const Error & err)
        {
            return err;
        }
        myOut << Separator;
        return process(forward<ArgsT>(args)...);
    }
    template<class T>
    Error process(T && curParameter) // если дошли до последнего параметра
    {
        try
        {
            parameterToStream(curParameter);
        }
        catch(const Error & err)
        {
            return err;
        }
        return Error::NoError;
    }
};