#include "ExpressionTree.h"
#include <iostream>

using namespace std;

ExpressionTree::ExpressionTree(void) 
    : root(nullptr) { }


bool ExpressionTree::empty(void) const { return this->root == nullptr; }


int ExpressionTree::height(void) { this->height(this->root); }


void ExpressionTree::insert(const string newData)
{
    Node* newNode = new Node{newData};
    insert(this->root, newNode);
}


void ExpressionTree::print(Node* node)
{
    if(node != nullptr) 
    {
        if(node->type == OPERAND) 
            cout << node->data;
        else 
        {
            cout << "(";
            print(node->left);
            cout << node->data;
            print(node->right);
            cout << ")";            
        }
    }
}


int ExpressionTree::max(const int x, const int y) { return (x > y) ? x : y; }


int ExpressionTree::height(Node* node)
{
    if(!node)
        return 0;
    else
        return 1 + max(height(node->left), height(node->right));
}


void ExpressionTree::print(void)
{
    this->print(this->root);
}


void ExpressionTree::insert(Node* node, Node* newData)
{
    if(this->empty())
    {
        this->root = newData;
        newData->inserted = true;
        return;
    }
    else if(node->type == OPERATOR)
    {
        if(node->left == nullptr)
        {
            node->left = newData;
            newData->inserted = true;
            return;
        }
        else if(node->right == nullptr)
        {
            node->right = newData;
            newData->inserted = true;
            return;
        }
        else
        {
            insert(node->left, newData);
            if(!newData->inserted)
                insert(node->right, newData);
        }
    }
    else if(node->type == OPERAND)
    { 
        return;
    }
}


void ExpressionTree::del(Node* node)
{
    if(node->left == nullptr)
    {
        transplant(node, node->right);

        delete node;
        node = nullptr;
    }
    else if(node->right == nullptr)
    {
        transplant(node, node->left);

        delete node;
        node = nullptr;
    }
    else
    {
        Node* bigger = leftmost(node->right);

        if(bigger != node->right)
        {
            transplant(bigger, bigger->right);
            bigger->right = node->right;
            node->right->parent = bigger;
        }

        transplant(node, bigger);
        bigger->left = node->left;
        node->left->parent = bigger;

        delete node;
        node = nullptr;
    }
}

Node* ExpressionTree::leftmost(Node* root)
{
    while(root->left != nullptr)
        root = root->left;
    return root;
}

void ExpressionTree::transplant(Node* u, Node* v)
{
    if(u->parent == nullptr)
        this->root = v;
    else if(u == u->parent->left)
        u->parent->left = v;
    else if(u == u->parent->right)
        u->parent->right = v;
    if(v != nullptr)
        v->parent = u->parent;
}


ExpressionTree::~ExpressionTree()
{
    this->del(this->root);
}