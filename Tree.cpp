#include "Tree.h"
#include <math.h>

CNode::~CNode()
{
    if (left != NULL)  delete left;
    if (right != NULL)  delete right;
    left = NULL;
    right = NULL;
}

NUMB::NUMB(double val)
{
    left = NULL;
    right = NULL;
    num = val;
}

VARB::VARB(char t_var)
{
    left = NULL;
    right = NULL;
    var = t_var;
}

SIGN::SIGN(char t_data, CNode* t_left, CNode* t_right)
{
    left = t_left;
    right = t_right;
    sign = t_data;
}

FUNC::FUNC(string t_str, CNode* t_left)
{
    left = t_left;
    right = NULL;
    func = t_str;
}

void NUMB::GoDump(int tab)
{
    if(this != NULL)
    {
        int i = 0;
        for(i = 0; i < tab - 1; i++)
        { 
            cout <<"    ";
        }
        cout << num; //выводит большие числа в виде X.XXXXXe+XX
        cout << endl;
    }
}

void SIGN::GoDump(int tab)
{
    if(this != NULL)
    {
        int i = 0;
        left -> GoDump(tab + 1);
        for(i = 0; i < tab - 1; i++)
        { 
            cout <<"    ";
        }
        cout << sign;
        cout << endl;
        right -> GoDump(tab + 1);
    }
}

void VARB::GoDump(int tab)
{
    if(this != NULL)
    {
        int i = 0;
        for(i = 0; i < tab - 1; i++)
        { 
            cout <<"    ";
        }
        cout << var;
        cout << endl;
    }
}

void FUNC::GoDump(int tab)
{
    if(this != NULL)
    {
        int i = 0;
        left -> GoDump(tab + 1);
        for(i = 0; i < tab - 1; i++)
        { 
            cout <<"    ";
        }
        cout << func;
        cout << endl;
    }
}
tree_print::tree_print(const char* name):
output(name)
{
    output << "\\documentclass[a4paper, 12pt]{article}\n\
    \\usepackage[T2A,T1]{fontenc}\n\
    \\usepackage[utf8]{inputenc}\n\
    \\usepackage[russian,english]{babel}\n\
    \\usepackage{amsmath}\n\
    \\usepackage{qtree}\n\
    \\usepackage{graphicx}\n\
    \\usepackage{tikz-qtree}\n\
    \\begin{document}\n\
    \\begin{otherlanguage*}{russian}\n\
    Печать дерева, поехали!" << endl;
}

tree_print::~tree_print() {
    tree_print::output << endl;
    tree_print::output << "\\end{otherlanguage*}\n\
    \\end{document}" << endl;
    tree_print::output.close();
}

void tree_print::print_data_(CNode* tree, int special_characters) {
    if (tree->GetType() == Number) {
        tree_print::output << tree->GetNum();
        cout << tree->GetNum();
    } else if (tree->GetType() == Sign) {
        if (tree->GetSign() == '^' && special_characters) {
            tree_print::output << "\\char94";
        } else {
            tree_print::output << tree->GetSign();
            cout << tree->GetSign();
        }
    } else if (tree->GetType() == Varible) {
        cout << tree->GetVar();
        tree_print::output << tree->GetVar();
    } else if (tree->GetType() == Function) {
        tree_print::output << tree->GetFun();
    }
}

void tree_print::equation(CNode* tree) {
    tree_print::output << "\n Your expression is:\n" << "$$";
    tree_print::print_equation_(tree);
    tree_print::output << "$$" << endl;
}

void tree_print::print_equation_(CNode* tree) {
    if (tree->GetType() != Function) {
        if (tree->GoLeft() != NULL) { 
            if ((tree->GoLeft()->GetType() == Number)||(tree->GoLeft()->GetType() == Varible)) {
                tree_print::print_equation_(tree->GoLeft());
            } else {
                tree_print::output << "\\left(";
                tree_print::print_equation_(tree->GoLeft());
                tree_print::output << "\\right)";
            }
        }
    } else {
        tree_print::print_data_(tree);
        tree_print::output << "\\left(";
        cout << tree->GetFun() << "(";
        tree_print::print_equation_(tree->GoLeft());
        tree_print::output << "\\right)";
        cout << ")";
    }
    if (tree->GetType() != Function) print_data_(tree);
    if (tree->GoRight() != NULL) {
        if ((tree->GoRight()->GetType() == Number)||(tree->GoRight()->GetType() == Varible)) {
            tree_print::print_equation_(tree->GoRight());
        } else {
            tree_print::output << "\\left(";
            tree_print::print_equation_(tree->GoRight());
            tree_print::output << "\\right)";
        }
    }
}

void tree_print::tree(CNode* tree) {
    tree_print::output << "\n Your tree is:\n\
    \\begin{center}\n\
    \\resizebox{\\linewidth}{!}{\\begin{tikzpicture}[sibling distance = \\baselineskip]\n\
    \\tikzset{every tree node/.style={align=center}}\n\
    \\tikzset{level 1+/.style={level distance=3\\baselineskip}}\n\
    \\Large \\Tree";
    tree_print::print_tree_(tree);
    tree_print::output << endl;
    tree_print::output << "\\end{tikzpicture}}\n\
    \\end{center}\n" << endl;
}

void tree_print::print_tree_(CNode* tree) {
    if (tree->GoLeft() != NULL) { 
        tree_print::output << " [. \\node[circle,draw=red] {";
        tree_print::print_data_(tree, 1);
        tree_print::output << "}; ";
        tree_print::print_tree_(tree->GoLeft());
    }
    if ((tree->GetType() == Number)||(tree->GetType() == Varible)) {
        tree_print::output << " [. \\node[circle,draw=green]{";
        tree_print::tree_print::print_data_(tree, 1);
        output << "}; ]";
    }
    if (tree->GoRight() != NULL) tree_print::print_tree_(tree->GoRight());
    if (tree->GetType() == Sign || tree->GetType() == Function) tree_print::output << " ]";
}


CNode* const_optimization(const CNode* subtree)
{
    {
        switch (subtree->type)
        {
        case Number:
        {
            return new CNode(subtree->num);
            break;
        }
        case Sign:
        {
             switch (subtree->sign)
             {
             case '+':
             {
                 if ((subtree->left->type == Number) && (subtree->right->type == Number))
                {
                     return new CNode(subtree->left->num + subtree->right->num);
                }
                else
                {
                    return new CNode('+', const_optimization(subtree->left), const_optimization(subtree->right));
                }
                 break;
            }
             case'-':
            {
                if ((subtree->left->type == Number) && (subtree->right->type == Number))
                {
                    return new CNode(subtree->left->num - subtree->right->num);
                }
                else
                {
                    return new CNode('-', const_optimization(subtree->left), const_optimization(subtree->right));
                }
                break;
            }
            case '*':
            {
                if ((subtree->left->type == Number) && (subtree->right->type == Number))
                {
                    return new CNode(subtree->left->num * subtree->right->num); 
                }
                else
                {
                    return new CNode('*', const_optimization(subtree->left), const_optimization(subtree->right));
                }
                break;
            }
            case '/':
            {
                if ((subtree->left->type == Number) && (subtree->right->type == Number))
                {
                    return new CNode(subtree->left->num / subtree->right->num); 
                }
                else
                {
                    return new CNode('/', const_optimization(subtree->left), const_optimization(subtree->right));
                }
                     break;
            }
            case'^':
            {
                if ((subtree->left->type == Number) && (subtree->right->type == Number))
                {
                    return new CNode(pow(subtree->left->num, subtree->right->num));
                }
                else
                {
                    return new CNode('^', const_optimization(subtree->left), const_optimization(subtree->right));
                }
                break;
            }
        }
        }
        case Varible:
        {
            return new CNode('x');
            break;
        }
        case Function:
        {
            if (strcmp(subtree->func.c_str(), "sin") == 0)
            {
                return new CNode("sin", const_optimization(subtree->left));
            }
            else if (strcmp(subtree->func.c_str(), "cos") == 0)
            {
                return new CNode("cos", const_optimization(subtree->left));
            }
            else if (strcmp(subtree->func.c_str(), "ln") == 0)
            {
                return new CNode("ln", const_optimization(subtree->left));
            }
            break;
        }
        }

    }
    return NULL;
}

CNode* derivate(const CNode* subtree)
{
    switch (subtree->type)
    {
    case Number:
    {
        return new CNode(0.0);
        break;
    }
    case Sign:
    {
        switch (subtree->sign)
        {
            case '+':
            {
                return new CNode('+', derivate(subtree->left), derivate(subtree->right));
                break;
            }
            case'-':
            {
                return new CNode('-', derivate(subtree->left), derivate(subtree->right));
                break;
            }
            case '*':
            {
                return new CNode('+', new CNode('*',\
                derivate(subtree->left), subtree->right),\
                new CNode('*', subtree->left, derivate(subtree->right)));
                break;
            }
            case '/':
            {
                return new CNode('/', new CNode('-',\
                new CNode('*', derivate(subtree->left),\
                subtree->right), new CNode('*', subtree->left,\
                derivate(subtree->right))), \
                new CNode('^', derivate(subtree->left), new CNode(2.0)));
                break;
            }
            case'^':
            {
                return new CNode('*', new CNode('^',\
                subtree->left, subtree->right),\
                new CNode('+', new CNode('*', new CNode('/',\
                subtree->left, subtree->right),\
                derivate(subtree->left)), new CNode('*', \
                new CNode("ln", subtree->left), derivate(subtree->right))));
                break;
            }
        }
    }
    case Varible:
    {
        return new CNode(1.0);
        break;
    }
    case Function:
    {
        if (strcmp(subtree->func.c_str(), "sin") == 0)
        {
            return new CNode('*', new CNode("cos", subtree->left), derivate(subtree->left));
        }
        else if (strcmp(subtree->func.c_str(), "cos") == 0)
        {
            return new CNode('*', new CNode('-', new CNode(0.0), new CNode("sin", subtree->left)), derivate(subtree->left));
        }
        else if (strcmp(subtree->func.c_str(), "ln") == 0)
        {
            return new CNode('/', new CNode(1.0), derivate(subtree->left));
        }
            // else if (strcmp(subtree->func.c_str(), "tg") == 0)
        {
             //return new CNode("/", new CNode (1.0), derivate(subtree->left));
        }
        break;
    }
    }
    return NULL;
}
