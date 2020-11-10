#include <iostream>
#include <string>
#include <sstream>
#include "error.hpp"
#include "serializer.hpp"
#include "deserializer.hpp"
using namespace std;


struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer & serializer)
    {
        return serializer(a, b, c);
    }
    template <class Deserializer>
    Error deserialize(Deserializer & deserializer)
    {
        return deserializer(a, b, c);
    }
};


struct DataWrong
{
    int a;
    bool b;
    string c;

    template <class Serializer>
    Error serialize(Serializer & serializer)
    {
        return serializer(a, b, c);
    }
    template <class Deserializer>
    Error deserialize(Deserializer & deserializer)
    {
        return deserializer(a, b, c);
    }
};


struct Datasmall
{
    uint64_t a;
    bool b;

    template <class Serializer>
    Error serialize(Serializer & serializer)
    {
        return serializer(a, b);
    }
    template <class Deserializer>
    Error deserialize(Deserializer & deserializer)
    {
        return deserializer(a, b);
    }
};


void defaultWorkTest()
{
    Data x { 1, true, 2 };
    stringstream stream;
    Serializer serializer(stream);
    serializer.save(x);
    Data y { 0, false, 0 };
    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);
    assert(err == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
}


void notUint64Test()
{
    DataWrong x { -1, true, "2" };
    stringstream stream;
    Serializer serializer(stream);
    const Error err = serializer.save(x);
    assert(err == Error::CorruptedArchive);
    DataWrong y { 1, true, "2" };
    const Error errsec = serializer.save(x);
    assert(errsec == Error::CorruptedArchive);
}


void wrongDeserialize()
{
    Datasmall x {777, true};
    stringstream stream;
    Serializer serializer(stream);
    serializer.save(x);
    stream << ' ' << "string";
    Data y { 0, false, 0 };
    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);
    assert(err == Error::CorruptedArchive);
}


int main(int argc, char* argv[])
{
    defaultWorkTest();
    notUint64Test();
    wrongDeserialize();
    cout << "Success!" << endl;
    return 0;
}