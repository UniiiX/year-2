#ifndef PRINTCOMMANDLINECOLORLESSSTRATEGY_H
#define PRINTCOMMANDLINECOLORLESSSTRATEGY_H

#include <iostream>

#include "PrintCommandLineStrategy.h"

namespace bst
{
template <typename T>
class PrintCommandLineColorlessStrategy : public PrintCommandLineStrategy<T, Node>
{
public:
    PrintCommandLineColorlessStrategy() {}
    virtual ~PrintCommandLineColorlessStrategy() {}

private:
    void printSubtree(const Node<T>* target, const std::string & indent = "") const override
    {
        if (!target)
            return;
        printSubtree(target->getRight(), indent + '\t');
        std::cout << indent << target->getKey() << std::endl;
        printSubtree(target->getLeft(), indent + '\t');
    }
};
}

#endif // PRINTCOMMANDLINECOLORFULSTRATEGY_H
