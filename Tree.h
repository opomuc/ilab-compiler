#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#ifndef NODE_H
#define NODE_H


enum c_type
{
    Number,
    Sign,
    Varible,
    Function
};

class CNode
{
    private:
        c_type type;
        double num;
        char sign;
        char var;
        string func;
        CNode* left;
        CNode* right;
    public:
        CNode();
        CNode(double val);
        CNode(char t_var);
        CNode(char data, CNode* t_left, CNode* t_right);
        CNode(string, CNode* t_left);
        ~CNode();
        c_type GetType() { return type; }
        double GetNum() { return num; }
        char GetSign() { return sign; }
        char GetVar() { return var; }
        string GetFun() { return func; }
        CNode* GoLeft() { return left; }
        CNode* GoRight() { return right; }
        void GoDump(int tab);
        friend CNode* derivate(const CNode*);
        friend CNode* const_optimization(const CNode*);
};

void print_data(ofstream& latex, CNode* tree);
int print_node(ofstream& latex, CNode* tree);
int print_graph(ofstream& output, CNode* tree);
int print_tree(CNode* tree);

#endif 