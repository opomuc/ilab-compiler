#include "Tree.h"

#ifndef MATH_H
#define MATH_H


class Math
{
    private:
        string::iterator S;
        string str;
    public:
        Math();
        string GetEquation();
        string PrepareEquation();
        void PutStr(string st);
        CNode* GetExp();                      //Exp :: = MulDiv {['+' '-']MulDiv}*
        CNode* GetMulDiv();                   //MulDiv :: = Pow {['*' '/'] Pow}*
        CNode* GetPow();                      //Pow :: = Pas {['^'] Pas}
        CNode* GetPas();                      //Pas:: = '(' Exp ')' | Num | F | x
        CNode* GetFunc();                     //Func:: = f '(' Exp ')' 
        CNode* GetNum();                      //Num :: = ['0' - '9']+
};

#endif