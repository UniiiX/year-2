#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <Node.h>
#include <BinarySearchTreeFactory.h>
#include <RedBlackTreeFactory.h>
#include <SplayTreeFactory.h>

namespace bst
{
    template <typename, typename>
    class Node;


    template <typename K, typename V>
    class BinarySearchTree
    {
        friend class BinarySearchTreeFactory<K, V>;
        friend class RedBlackTreeFactory<K, V>;
        friend class SplayTreeFactory<K, V>;

    public:
        virtual ~BinarySearchTree();

        virtual const Node<K, V>* search(const K & key);
        virtual BinarySearchTree & insert(const K & key, const V & value);
        virtual BinarySearchTree & remove(const K & key);

        const Node<K, V>* minimum(Node<K, V>* target) const;
        const Node<K, V>* maximum(Node<K, V>* target) const;
        const Node<K, V>* predecessor(Node<K, V>* target) const;
        const Node<K, V>* successor(Node<K, V>* target) const;

        const Node<K, V>* getRoot() const;
        const TreeType getType() const;

    protected:
        Node<K, V>* root;
        BinarySearchTreeImpl<K, V>* impl;

        BinarySearchTree(BinarySearchTreeImpl<K, V>* impl);
    };


    template <typename K, typename V>
    BinarySearchTree<K, V>::BinarySearchTree(BinarySearchTreeImpl<K, V>* impl):
        root(nullptr),
        impl(impl)
    {

    }

    template <typename K, typename V>
    BinarySearchTree<K, V>::~BinarySearchTree()
    {
        impl->free(root);
        delete impl;
    }

    template <typename K, typename V>
    const Node<K, V>* BinarySearchTree<K, V>::minimum(Node<K, V>* target) const
    {
        return impl->minimum(target);
    }

    template <typename K, typename V>
    const Node<K, V>* BinarySearchTree<K, V>::maximum(Node<K, V>* target) const
    {
        return impl->maximum(target);
    }

    template <typename K, typename V>
    const Node<K, V>* BinarySearchTree<K, V>::predecessor(Node<K, V>* target) const
    {
        return impl->predecessor(target);
    }

    template <typename K, typename V>
    const Node<K, V>* BinarySearchTree<K, V>::successor(Node<K, V>* target) const
    {
        return impl->successor(target);
    }

    template <typename K, typename V>
    const Node<K, V>* BinarySearchTree<K, V>::search(const K & key)
    {
        return impl->search(root, key);
    }

    template <typename K, typename V>
    BinarySearchTree<K, V> & BinarySearchTree<K, V>::insert(const K & key, const V & value)
    {
        impl->insert(root, key, value);
        return *this;
    }

    template <typename K, typename V>
    BinarySearchTree<K, V> & BinarySearchTree<K, V>::remove(const K & key)
    {
        impl->remove(root, key);
        return *this;
    }

    template <typename K, typename V>
    const Node<K, V>* BinarySearchTree<K, V>::getRoot() const
    {
        return root;
    }

    template <typename K, typename V>
    const TreeType BinarySearchTree<K, V>::getType() const
    {
        return impl->getType();
    }
}

#endif // BINARYSEARCHTREE_H
