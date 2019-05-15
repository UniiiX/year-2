#ifndef ABSTRACTTREEFACTORY_H
#define ABSTRACTTREEFACTORY_H

#include <BinarySearchTree.h>

namespace bst
{
    template <typename, typename>
    class BinarySearchTree;

    template <typename K, typename V>
    class AbstractTreeFactory
    {
    public:
        AbstractTreeFactory() {}
        virtual ~AbstractTreeFactory() {}

        virtual BinarySearchTree<K, V> create() const = 0;
    };
}

#endif // ABSTRACTTREEFACTORY_H
