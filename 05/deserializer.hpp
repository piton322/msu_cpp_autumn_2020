#pragma once
#include <iostream>
#include "error.hpp"
using namespace std;


class Deserializer
{
public: // паблик секция из подсказки к домашней работе
    explicit Deserializer(istream & in): myIn(in){}

    template <class T>
    Error load(T& object)
    {
        return object.deserialize(*this);
    }

    template <class ... ArgsT>
    Error operator()(ArgsT && ... args)
    {
        return process(forward<ArgsT>(args)...);
    }
    
private:
    istream & myIn;

    void parameterFromStream(bool & parameter);
    void parameterFromStream(uint64_t & parameter);

    template <class T>
    void parameterFromStream(T) // не bool и не uint64_t
    {
        throw Error::CorruptedArchive;
    }
    template<class T, class... ArgsT>

    Error process(T && curParameter, ArgsT && ... args)
    {
        try
        {
            parameterFromStream(curParameter);
        }
        catch(Error err)
        {
            return err;
        }
        //myIn >> Separator;
        return process(forward<ArgsT>(args)...);
    }

    template<class T>
    Error process(T && curParameter) // если дошли до последнего параметра
    {
        try
        {
            parameterFromStream(curParameter);
        }
        catch(const Error & err)
        {
            return err;
        }
        return Error::NoError;
    }
};