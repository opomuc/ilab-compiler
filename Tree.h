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
    protected:
        CNode* left;
        CNode* right;
    public:
        virtual ~CNode();
        CNode* GoLeft() { return left; }
        CNode* GoRight() { return right; }
        virtual void GoDump(int tab) = 0; //Чисто виртуальная функция
};

class SCNode: CNode
{
    private:
        char sign;
    public:
        SCNode(char data, CNode* t_left, CNode* t_right);
        char GetSign() { return sign; }
        void GoDump(int tab);
};

class NCNode: CNode
{
    private:
        double num;
    public:
        NCNode(double val);
        double GetNum() { return num; }
        void GoDump(int tab);
};

class VCNode: CNode
{
    private:
        char var;
    public:
        VCNode(char t_var);
        char GetVar() { return var; }
        void GoDump(int tab);
};

class FCNode: CNode
{
    private:
        string func;
    public:
        FCNode(string, CNode* t_left);
        string GetFun() { return func; }
        void GoDump(int tab);
};

class tree_print {
    std::ofstream output;
    void print_equation_(CNode* tree);
    void print_data_(CNode* tree, int special_characters=0);
    void print_tree_(CNode* tree);
    //ofstream create_tex();
public:
    tree_print(const char*);
    ~tree_print();
    void equation(CNode* tree);
    void tree(CNode* tree);
};
#endif 