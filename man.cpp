#include "Math.h"
#include "Tree.h"

int main()
{
    Math test;
    test.PutStr(test.GetEquation());
    test.PutStr(test.PrepareEquation());
    CNode* node = test.GetExp();
    node -> GoDump(1);

    CNode* der = derivate(node);
    der -> GoDump(1);
    print_tree(der);
    delete der;
    delete node;
    return 0;
}
