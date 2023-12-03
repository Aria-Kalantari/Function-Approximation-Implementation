#include "Functions.h"
#include "Function.h"
#include <ctime>
#include <stdexcept>

Functions::Functions(const int size)
    : size(size),
      functions(new Function[size]{ })
{
    srand(time(nullptr));
    int random = 0;
    int offset = 0;

    for(int i = 0; i < size; ++i)
    {
        random = rand();    
        functions[i].generate(random + offset);
        offset += 1;
    }
}


Function& Functions::operator[](const int index)
{
    if(index < 0 || index >= size)
        throw std::out_of_range("Index is out of range.");
    else
        return this->functions[index];
}


const string& Functions::fit()
{
    double minValue = 10000000;
    int minIndex = 0;

    for(int i = 0; i < size; ++i)
        if(functions[i].MSE() < minValue)
        {
            minValue = functions[i].MSE();
            minIndex = i;
        }
    
    return functions[minIndex].getFunction();
}


Functions::~Functions() { delete[] this->functions; }