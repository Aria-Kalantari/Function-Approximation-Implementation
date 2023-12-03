#ifndef NODE_H
#define NODE_H

#pragma once

#include "ExpressionTree.h"
#include <string>

enum Type { OPERATOR, OPERAND };

class Node
{
    friend class ExpressionTree;
    friend class Function;

public:
    Node(const std::string& = "0");

    bool isOperator(void) const;

private:
    std::string data;
    enum Type type;
    bool inserted;

    Node* left;
    Node* right;
    Node* parent;
};

#endif