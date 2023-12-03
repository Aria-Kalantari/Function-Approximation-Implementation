#include "Node.h"

Node::Node(const std::string& data)
    : data(data),
      inserted(false),
      left(nullptr),
      right(nullptr),
      parent(nullptr) 
{
    if(this->isOperator())
        type = OPERATOR;
    else
        type = OPERAND;
}


bool Node::isOperator(void) const
{
    return (this->data == "+" || this->data == "-" ||
            this->data == "*" || this->data == "/" ||
            this->data == "^");
}