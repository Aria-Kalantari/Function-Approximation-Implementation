#include "ExpressionTree.cpp"
#include "Function.cpp"
#include "Node.cpp"
#include "Functions.cpp"
#include <iostream>

using namespace std;

int main(void)
{
    Functions functions(50);
    for(int i = 0; i < 50; ++i)
    {
        cout << i + 1 << "> " << functions[i].getFunction() << endl;
    }

    cout << endl << "**************************************************************************************************************" << endl;

    for(int i = 0; i < 50; ++i)
    {
        cout <<  i + 1 << "> " << functions[i].evaluate(90, 45678) << endl;
    }

    cout << endl << "**************************************************************************************************************" << endl;

    for(int i = 0; i < 50; ++i)
    {
        cout << i + 1 << "> " << functions[i].evaluate(80, 456789) << endl;
    }

    cout << endl << "**************************************************************************************************************" << endl;


    for(int i = 0; i < 50; ++i)
    {
        cout << i + 1 << "> " << functions[i].evaluate(4567, 395678) << endl;
    }

    cout << endl << "**************************************************************************************************************" << endl;

    cout << functions.fit() << endl;

    return 0;
}