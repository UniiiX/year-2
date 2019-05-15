#ifndef BINARYSEARCHTREESFACADE_H
#define BINARYSEARCHTREESFACADE_H

#include <BinarySearchTree.h>

namespace bst
{
    template <typename K, typename V>
    class BinarySearchTreesFacade
    {
    public:
        BinarySearchTreesFacade(const BinarySearchTreesFacade &) = delete;
        BinarySearchTreesFacade(BinarySearchTreesFacade &&) = delete;
        virtual ~BinarySearchTreesFacade() {}
        BinarySearchTreesFacade & operator=(const BinarySearchTreesFacade &) = delete;
        BinarySearchTreesFacade & operator=(BinarySearchTreesFacade &&) = delete;

        static BinarySearchTreesFacade & getInstance()
        {
            static BinarySearchTreesFacade instance;
            return instance;
        }

        BinarySearchTree<K, V> & insert(
            BinarySearchTree<K, V> & target,
            const K & key,
            const V & value) const
        {
            target.insert(key, value);
        }

        BinarySearchTree<K, V> & remove(
            BinarySearchTree<K, V> & target,
            const K & key) const
        {
            target.remove(key);
        }

        void search(
            BinarySearchTree<K, V> & target,
            const K & key) const
        {
            target.search(key);
        }

        BinarySearchTree<K, V> create(const TreeType & type) const
        {
            switch (type)
            {
                case TreeType::binarySearchTree:
                {
                    return BinarySearchTreeFactory<K, V>().create();
                }
                case TreeType::splayTree:
                {
                    return SplayTreeFactory<K, V>().create();
                }
                case TreeType::redBlackTree:
                {
                    return RedBlackTreeFactory<K, V>().create();
                }
            }
        }

        void print(const BinarySearchTree<K, V> & target) const
        {
            PrinterProxy<K, V>::print(target);
        }

    private:
        BinarySearchTreesFacade() {}
    };
}

#endif // BINARYSEARCHTREESFACADE_H
