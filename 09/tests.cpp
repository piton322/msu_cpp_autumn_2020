#include "threadsort.hpp"
#include <iostream>
#include "error.hpp"


void makeInput()
{
    ofstream file("input.txt");
    if(!file)
    {
        throw Error::InputFileError;
    }
    for(size_t i = 0; i < 100000; i++)
    {
        uint64_t number = rand() % 100000;
        //cout << number << " ";
        file.write(reinterpret_cast<char*>(& number), sizeof(uint64_t));
    }
    //cout << endl;
    file.close();
}


void outputTest()
{
    ifstream f("output.txt");
    f.seekg (0, f.end);
	my_type size_out = f.tellg() / my_size;
	f.seekg(0, f.beg);
    my_type * mas = new my_type [size_out + 1];
    for (int i = 0; i < size_out; i++)
    {
        f >> mas[i];
    }
    assert(is_sorted(mas, mas + size_out) == 1);
}


int main()
{
    makeInput();
    sort_file("input.txt", "output.txt");
    outputTest();
    cout << "Success!" << endl;
    return 0;
}
