#ifndef PRINTCOMMANDLINECOLORFULSTRATEGY_H
#define PRINTCOMMANDLINECOLORFULSTRATEGY_H

#include <iostream>

#include "PrintCommandLineStrategy.h"
#include "RedBlackNode.h"

namespace bst
{
template <typename T>
class PrintCommandLineColorfulStrategy : public PrintCommandLineStrategy<T, RedBlackNode>
{
public:
    PrintCommandLineColorfulStrategy() {}
    virtual ~PrintCommandLineColorfulStrategy() {}

private:
    void printSubtree(const RedBlackNode<T>* target, const std::string & indent = "") const override
    {
        if (!target)
            return;
        printSubtree(dynamic_cast<RedBlackNode<T>*>(target->getRight()), indent + '\t');
        std::cout << indent << target->getKey() << "{";
        (target->getColor() == Color::black) ? std::cout << "B" : std::cout << "R";
        std::cout << "}" << std::endl;
        printSubtree(dynamic_cast<RedBlackNode<T>*>(target->getLeft()), indent + '\t');
    }
};
}

#endif // PRINTCOMMANDLINECOLORFULSTRATEGY_H
