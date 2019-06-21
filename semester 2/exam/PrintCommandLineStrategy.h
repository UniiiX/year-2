#ifndef PRINTCOMMANDLINESTRATEGY_H
#define PRINTCOMMANDLINESTRATEGY_H

#include <string>
#include <PrintStrategy.h>


namespace bst
{
template <typename T, template <typename> typename Node>
class PrintCommandLineStrategy : public PrintStrategy<T, Node>
{
public:
    PrintCommandLineStrategy() {}
    virtual ~PrintCommandLineStrategy() {}

    void print(const BinarySearchTree<T, Node> & target) const override
    {
        printSubtree(target.getRoot());
    }

private:
    virtual void printSubtree(const Node<T>* target, const std::string & indent = "") const = 0;
};
}

#endif // PRINTCOMMANDLINESTRATEGY_H
