#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#pragma once

#include "Function.h"

class Functions
{
public:
    Functions(const int);

    Function& operator[](const int);
    
    const string& fit(void);

    ~Functions();

private:
    Function* functions;
    int size;
};

#endif