#ifndef PRINTSTRATEGY_H
#define PRINTSTRATEGY_H

#include <BinarySearchTree.h>

namespace bst
{
template <typename, template <typename> typename>
class BinarySearchTree;

template <typename T, template <typename> typename Node>
class PrintStrategy
{
public:
    PrintStrategy() {}
    virtual ~PrintStrategy() {}

    virtual void print(const BinarySearchTree<T, Node> & target) const = 0;
};
}

#endif // PRINTSTRATEGY_H
