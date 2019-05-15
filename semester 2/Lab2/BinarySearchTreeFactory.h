#ifndef BINARYSEARCHTREEFACTORY_H
#define BINARYSEARCHTREEFACTORY_H

#include <AbstractTreeFactory.h>
#include <BinarySearchTreeImpl.h>

namespace bst
{
    template <typename K, typename V>
    class BinarySearchTreeFactory : public AbstractTreeFactory<K, V>
    {
    public:
        BinarySearchTreeFactory() {}
        virtual ~BinarySearchTreeFactory() {}

        BinarySearchTree<K, V> create() const override
        {
            auto impl = new BinarySearchTreeImpl<K, V>;
            return BinarySearchTree<K, V>(impl);
        }
    };
}

#endif // BINARYSEARCHTREEFACTORY_H
