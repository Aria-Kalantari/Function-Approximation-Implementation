#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

#pragma once

#include "Node.h"
#include <string>
#include <iostream>

class ExpressionTree
{
public:
    ExpressionTree(void);
    
    bool empty(void) const;

    int height(void);

    void insert(const std::string);

    void print(void);

    ~ExpressionTree();

protected:
    Node* root;

    int max(const int, const int);
    
    int height(Node*);

    void insert(Node*, Node*);

    void print(Node*);
    
    void del(Node*);
    Node* leftmost(Node*);
    void transplant(Node*, Node*);
};

#endif