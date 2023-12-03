#include "Function.h"
#include "ExpressionTree.h"
#include "Node.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>
#include <string>
#include <cmath>

using namespace std;

const string Function::variables[4] = {"x", "sin(x)", "y", "cos(x)"};
const string Function::constants[21] = {"(-10)", "(-9)", "(-8)", "(-7)", "(-6)", "(-5)", "(-4)", "(-3)", "(-2)", "(-1)",
                                        "11", "10", "9", "8", "7", "6", "5", "4", "3", "2", "1"};
const string Function::operators[5] = {"+", "-", "*", "/", "^"};

Function::Function(void) : ExpressionTree() 
{
    generate(); 
    toFunction(this->root);
    fixup();
}


const string& Function::getFunction(void) const { return this->function; }


void Function::generate(const int random)
{
    Node* newNode;
    bool isNotValid;
    int offset = 0;

    int maxHeight = (random % 5) + 1;

    do
    {
        newNode = new Node{ };
        isNotValid = false;
        newNode = randomCharacter(newNode, (height(this->root) + 1 >= maxHeight), rand() + offset);
        offset += 1;
        insert(this->root, newNode);
        isNotValidFunction(this->root, isNotValid);
    } while(isNotValid);
    
}


double Function::evaluate(double x, double y)
{
    double grade = evaluate(this->root, x, y);
    if(function.find("y") == string::npos)
        grade -= y;
    grades.push_back(grade);
    return grade;
}


double Function::MSE(void)
{
    double MSE = 0;
    for(int i = 0; i < grades.size(); ++i)
        MSE += pow(grades[i], 2);
    MSE /= grades.size();
    return MSE;
}


void Function::toFunction(Node* node)
{
    if(node)
    {
        if (node->type == OPERAND) 
            function += node->data;
        else 
        {
            function += "(";
            toFunction(node->left);
            function += node->data;
            toFunction(node->right);
            function += ")";            
        } 
    }
}

void Function::fixup(void)
{
    if(function.find("y") == string::npos)
        function = "(" + function + "-y" + ")";
}


void Function::isNotValidFunction(Node* node,  bool& isNotValid)
{
    if(node)
    {
        if(node->type == OPERATOR && (node->left == nullptr || node->right == nullptr))
            isNotValid = true;
        isNotValidFunction(node->left, isNotValid);
        isNotValidFunction(node->right, isNotValid);
    }
}

Node* Function::randomCharacter(Node* newNode, bool maxHeight, const int random)
{
    if(maxHeight == 1) 
    {
        int varOrCon = random % 2;

        if(varOrCon == 1)
        {
            newNode->data = variables[random % 4];
            newNode->type = OPERAND;
        }
        else
        {
            newNode->data = constants[random % 21];
            newNode->type = OPERAND;
        }
    }
    else 
    {
        int percentage = random % 100 + 1;

        if (percentage >= 50) 
        {
            int varOrCon = random % 2;

            if(varOrCon == 0)
            {
                newNode->data = variables[random % 4];
                newNode->type = OPERAND;
            }
            else
            {
                newNode->data = constants[random % 21];
                newNode->type = OPERAND;
            }
        }
        else 
        {
            newNode->data = operators[random % 5];
            newNode->type = OPERATOR;
        }
    }
}


double Function::evaluate(Node* node, double x, double y)
{
    if(!node)
        return 0;
    
    if(!node->left && !node->right)
        return operandToNum(node->data, x, y);
    
    double leftValue = evaluate(node->left, x, y);
    double rightValue = evaluate(node->right, x, y);

    if(node->data == "+")
        return leftValue + rightValue;
    
    if(node->data == "-")
        return leftValue - rightValue;
    
    if(node->data == "*")
        return leftValue * rightValue;
    
    if(node->data == "^")
        return pow(leftValue, rightValue);
}

double Function::operandToNum(const string& operand, const double x, const double y)
{
    if(operand == "sin(x)")
        return sin(x);
    if(operand == "cos(x)")
        return cos(x);
    if(operand == "x")
        return x;
    if(operand == "y")
        return y;
    else
    {
        if(operand[0] == '(')
            return stoi(operand.substr(1, 2));
        else
            return stoi(operand);
    }
        return stoi(operand);
}