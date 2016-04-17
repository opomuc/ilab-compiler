#include "Math.h"
#include "Tree.h"

int main()
{
    Math test;
    test.PutStr(test.GetEquation());
    test.PutStr(test.PrepareEquation());
    CNode* node = test.GetExp();
    node -> GoDump(0);
    tree_print output("tree.tex");
    output.equation(node);
    output.tree(node);
    output.tree(derivate(node));
    std::cout <<std::endl;
    delete node;
    return 0;
}
