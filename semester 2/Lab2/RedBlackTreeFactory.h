#ifndef REDBLACKTREEFACTORY_H
#define REDBLACKTREEFACTORY_H

#include <AbstractTreeFactory.h>
#include <RedBlackTreeImpl.h>

namespace bst
{
    template <typename K, typename V>
    class RedBlackTreeFactory : public AbstractTreeFactory<K, V>
    {
    public:
        RedBlackTreeFactory() {}
        virtual ~RedBlackTreeFactory() {}

        BinarySearchTree<K, V> create() const override
        {
            auto impl = new RedBlackTreeImpl<K, V>;
            return BinarySearchTree<K, V>(impl);
        }
    };
}


#endif // REDBLACKTREEFACTORY_H
