#ifndef FUNCTION_H
#define FUNCTION_H

#pragma once

#include "ExpressionTree.h"
#include "Node.h"
#include <string>
#include <vector>

class Function : public ExpressionTree
{
public:
    Function(void);

    const string& getFunction(void) const;

    void generate(const int = 4);

    double evaluate(double, double);

    double MSE(void);

    ~Function() = default;

private:
    std::string function;
    std::vector<double> grades;

    static const std::string variables[4];
    static const std::string constants[21];
    static const std::string operators[5];

    void toFunction(Node*);
    void fixup(void);

    void isNotValidFunction(Node*, bool&);
    Node* randomCharacter(Node*, bool, const int);

    double evaluate(Node*, double, double);
    double operandToNum(const std::string&, const double, const double);
};

#endif