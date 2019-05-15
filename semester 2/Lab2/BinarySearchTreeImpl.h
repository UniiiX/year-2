#ifndef BINARYSEARCHTREEIMPL_H
#define BINARYSEARCHTREEIMPL_H

#include <Node.h>
#include <TreeType.h>
#include <BinarySearchTreeExceptions.h>

namespace bst
{
    template <typename, typename>
    class Node;

    template <typename K, typename V>
    class BinarySearchTreeImpl
    {
    public:
        BinarySearchTreeImpl() {}
        virtual ~BinarySearchTreeImpl() {}

        virtual Node<K, V>* search(Node<K, V>* & root, const K & key) const;
        virtual void insert(Node<K, V>* & root, const K & key, const V & value) const;
        virtual void remove(Node<K, V>* & root, const K & key) const;

        Node<K, V>* minimum(Node<K, V>* target) const;
        Node<K, V>* maximum(Node<K, V>* target) const;
        Node<K, V>* predecessor(Node<K, V>* target) const;
        Node<K, V>* successor(Node<K, V>* target) const;

        virtual const TreeType getType() const;

        void free(Node<K, V>* & root) const;


    protected:
        void swapKeys(Node<K, V>* first, Node<K, V>* second) const;
        void swapValues(Node<K, V>* first, Node<K, V>* second) const;

        Node<K, V>* searchParent(Node<K, V>* & root, const K & key) const;
        void rotate(Node<K, V>* & root, Node<K, V>* child) const;
    };

    template <typename K, typename V>
    void BinarySearchTreeImpl<K, V>::free(Node<K, V>* & root) const
    {
        if (!root)
            return;
        // NOTE: without following two lines -
        // error: invalid initialization of non-const reference of type ‘T&’ from an rvalue of type ‘T’
        auto left = root->getLeft();
        auto right = root->getRight();
        free(left);
        free(right);
        delete root;
    }

    template <typename K, typename V>
    void BinarySearchTreeImpl<K, V>::swapKeys(Node<K, V>* first, Node<K, V>* second) const
    {
        auto firstKey = first->getKey();
        first->setKey(second->getKey());
        second->setKey(firstKey);
    }

    template <typename K, typename V>
    void BinarySearchTreeImpl<K, V>::swapValues(Node<K, V>* first, Node<K, V>* second) const
    {
        auto firstValue = first->getValue();
        first->setValue(second->getValue());
        second->setValue(firstValue);
    }

    template <typename K, typename V>
    Node<K, V>* BinarySearchTreeImpl<K, V>::minimum(Node<K, V>* target) const
    {
        if (!target)
        {
            return nullptr;
        }
        Node<K, V>* result = target;
        while(target->getLeft())
        {
            return minimum(target->getLeft());
        }
        return result;
    }

    template <typename K, typename V>
    Node<K, V>* BinarySearchTreeImpl<K, V>::maximum(Node<K, V>* target) const
    {
        if (!target)
        {
            return nullptr;
        }
        Node<K, V>* result = target;
        while(target->getRight())
        {
            return maximum(target->getRight());
        }
        return result;
    }

    template <typename K, typename V>
    Node<K, V>* BinarySearchTreeImpl<K, V>::predecessor(Node<K, V>* target) const
    {
        if (target->getLeft())
        {
            return maximum(target->getLeft());
        }
        else
        {
            Node<K, V>* result = target;
            while (result && result != result->getParent()->getRight())
            {
                result = result->getParent();
            }
            return result;
        }
    }

    template <typename K, typename V>
    Node<K, V>* BinarySearchTreeImpl<K, V>::successor(Node<K, V>* target) const
    {
        if (target->getRight())
        {
            return minimum(target->getRight());
        }
        else
        {
            Node<K, V>* result = target;
            while (result && result != result->getParent()->getLeft())
            {
                result = result->getParent();
            }
            return result;
        }
    }

    // rotates left if child is the right child of its parent, or
    // rotates right if child is the left child of its parent
    template <typename K, typename V>
    void BinarySearchTreeImpl<K, V>::rotate(Node<K, V>* & root, Node<K, V>* child) const
    {
        if (!child)
        {
            throw InvalidNode("Can not rotate null-node");
            return;
        }

        // short references
        bool direction = (child == child->getParent()->getLeft()); // true - rotate right, false - left
        Node<K, V>* parent = child->getParent();
        Node<K, V>* grandparent = child->getGrandparent();

        if (grandparent)
        {
            (grandparent->getLeft() == parent) ? grandparent->setLeft(child) : grandparent->setRight(child);
        }
        else // parent was the root of the entire tree
        {
            root = child; // child becomes the new root
        }
        child->setParent(grandparent);

        (direction) ? parent->setLeft(child->getRight()) : parent->setRight(child->getLeft());
        if (direction)
        {
            if (child->getRight())
            {
                child->getRight()->setParent(parent);
            }
        }
        else
        {
            if (child->getLeft())
            {
                child->getLeft()->setParent(parent);
            }
        }

        (direction) ? child->setRight(parent) : child->setLeft(parent);
        parent->setParent(child);
    }

    // returns parent of the node with given key if the key is present in the tree, or
    // returns parent of the null node where given key would have been placed if it
    // was present in the tree.
    template <typename K, typename V>
    Node<K, V>* BinarySearchTreeImpl<K, V>::searchParent(Node<K, V>* & root, const K & key) const
    {
        Node<K, V>* parent = nullptr;
        Node<K, V>* current = root;
        while (current)
        {
            parent = current;
            if (current->getKey() > key)
            {
                current = current->getLeft();
            }
            else if (current->getKey() < key)
            {
                current = current->getRight();
            }
            else
            {
                parent = parent->getParent();
                break;
            }
        }
        return parent;
    }

    template <typename K, typename V>
    Node<K, V>* BinarySearchTreeImpl<K, V>::search(Node<K, V>* & root, const K & key) const
    {
        Node<K, V>* current = root;
        while (current)
        {
            if (current->getKey() > key)
            {
                current = current->getLeft();
            }
            else if (current->getKey() < key)
            {
                current = current->getRight();
            }
            else
            {
                return current;
            }
        }
        return nullptr;
    }

    template <typename K, typename V>
    void BinarySearchTreeImpl<K, V>::insert(Node<K, V>* & root, const K & key, const V & value) const
    {
        Node<K, V>* found = search(root, key);
        if (found)
        {
            // replacing old value with new one, cause duplicate keys are not allowed
            found->setValue(value);
        }
        else
        {
            Node<K, V>* toBeInserted = Node<K, V>::createColorless(key, value);
            if (!root)
            {
                root = toBeInserted;
                return;
            }
            Node<K, V>* parent = searchParent(root, key);

            // parent can't be nullptr, cause then we would have exited the function earlier on
            (parent->getKey() > key) ? parent->setLeft(toBeInserted) : parent->setRight(toBeInserted);
            toBeInserted->setParent(parent);
        }
    }

    template <typename K, typename V>
    void BinarySearchTreeImpl<K, V>::remove(Node<K, V>* & root, const K & key) const
    {
        Node<K, V>* found = search(root, key);
        if (!found)
        {
            throw AbsentKey("Can not remove absent key");
            return;
        }

        Node<K, V>* toBeRemoved = found;
        // set toBeRemoved to be found's predecessor if any
        if (toBeRemoved->getLeft())
        {
            toBeRemoved = maximum(toBeRemoved->getLeft());
        }
        auto parent = toBeRemoved->getParent();
        // child is only non-null child of toBeRemoved if any
        auto child = (toBeRemoved->getLeft()) ? toBeRemoved->getLeft() : toBeRemoved->getRight();

        if (root != toBeRemoved)
        {
            (toBeRemoved == parent->getRight()) ? parent->setRight(child) : parent->setLeft(child);
            swapKeys(toBeRemoved, found);
            swapValues(toBeRemoved, found);
        }
        else
        {
            root = child;
        }
        if (child) child->setParent(parent);

        delete toBeRemoved;
    }

    template <typename K, typename V>
    inline const TreeType BinarySearchTreeImpl<K, V>::getType() const
    {
        return TreeType::binarySearchTree;
    }
}

#endif // BINARYSEARCHTREEIMPL_H
