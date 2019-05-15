#ifndef SPLAYTREEIMPL_H
#define SPLAYTREEIMPL_H

#include <BinarySearchTree.h>

namespace bst
{
    template <typename K, typename V>
    class SplayTreeImpl : public BinarySearchTreeImpl<K, V>
    {
    public:
        SplayTreeImpl() {}
        virtual ~SplayTreeImpl() {}

        Node<K, V>* search(Node<K, V>* & root, const K & key) const override;
        void insert(Node<K, V>* & root, const K & key, const V & value) const override;
        void remove(Node<K, V>* & root, const K & key) const override;

        const TreeType getType() const override;

    protected:
        void splay(Node<K, V>* & root, Node<K, V>* target) const;
        Node<K, V>* split(Node<K, V>* & root, const K & key) const;
        void merge(Node<K, V>* & root, Node<K, V>* otherRoot) const;
    };


    template <typename K, typename V>
    void SplayTreeImpl<K, V>::splay(Node<K, V>* & root, Node<K, V>* target) const
    {
        while (root != target)
        {
            BinarySearchTreeImpl<K, V>::rotate(root, target);
        }
    }

    // puts the node with the given key into the root by calling splay method on it
    // then cuts off left child of the new root from its parent and returns it
    template <typename K, typename V>
    Node<K, V>* SplayTreeImpl<K, V>::split(Node<K, V>* & root, const K & key) const
    {
        if (!root)
        {
            return nullptr;
        }

        Node<K, V>* pivot;
        Node<K, V>* found = BinarySearchTreeImpl<K, V>::search(root, key);

        if (found)
        {
            pivot = found;
        }
        else
        {
            pivot = (BinarySearchTreeImpl<K, V>::successor(found)) ?
                BinarySearchTreeImpl<K, V>::successor(found) :
                BinarySearchTreeImpl<K, V>::predecessor(found);
        }

        splay(root, pivot);
        Node<K, V>* result = root->getLeft();
        if (result)
        {
            root->getLeft()->setParent(nullptr);
            root->setLeft(nullptr);
        }
        return result;
    }

    template <typename K, typename V>
    void SplayTreeImpl<K, V>::merge(Node<K, V>* & root, Node<K, V>* otherRoot) const
    {
        if (!otherRoot)
        {
            return;
        }
        if (!root)
        {
            root = otherRoot;
            return;
        }
        splay(root, BinarySearchTreeImpl<K, V>::minimum(root));
        root->setLeft(otherRoot);
        otherRoot->setParent(root);
    }

    template <typename K, typename V>
    Node<K, V>* SplayTreeImpl<K, V>::search(Node<K, V>* & root, const K & key) const
    {
        auto found = BinarySearchTreeImpl<K, V>::search(root, key);
        if (found)
            splay(root, found);
        return found;
    }

    template <typename K, typename V>
    void SplayTreeImpl<K, V>::insert(Node<K, V>* & root, const K & key, const V & value) const
    {
        BinarySearchTreeImpl<K, V>::insert(root, key, value);

        Node<K, V>* inserted = BinarySearchTreeImpl<K, V>::search(root, key);
        Node<K, V>* leftSubtreeRoot = split(root, key);

        if (leftSubtreeRoot)
        {
            leftSubtreeRoot->setParent(inserted);
            inserted->setLeft(leftSubtreeRoot);
        }
    }

    template <typename K, typename V>
    void SplayTreeImpl<K, V>::remove(Node<K, V>* & root, const K & key) const
    {
        Node<K, V>* toBeRemoved = BinarySearchTreeImpl<K, V>::search(root, key);
        if (!toBeRemoved)
        {
            throw AbsentKey("Can not remove absent key");
            return;
        }
        Node<K, V>* leftSubtreeRoot = split(root, key);

        root = root->getRight();
        if (root)
        {
            root->setParent(nullptr);
        }
        merge(root, leftSubtreeRoot);

        delete toBeRemoved;
    }

    template <typename K, typename V>
    inline const TreeType SplayTreeImpl<K, V>::getType() const
    {
        return TreeType::splayTree;
    }
}


#endif // SPLAYTREEIMPL_H
