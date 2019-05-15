#ifndef SPLAYTREEFACTORY_H
#define SPLAYTREEFACTORY_H

#include <AbstractTreeFactory.h>
#include <SplayTreeImpl.h>

namespace bst
{
    template <typename K, typename V>
    class SplayTreeFactory : public AbstractTreeFactory<K, V>
    {
    public:
        SplayTreeFactory() {}
        virtual ~SplayTreeFactory() {}

        BinarySearchTree<K, V> create() const override
        {
            auto impl = new SplayTreeImpl<K, V>;
            return BinarySearchTree<K, V>(impl);
        }
    };
}

#endif // SPLAYTREEFACTORY_H
