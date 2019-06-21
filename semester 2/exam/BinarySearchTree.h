#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <functional>

#include "Node.h"
#include "BinarySearchTreeExceptions.h"
#include "PrintCommandLineColorlessStrategy.h"

namespace bst
{
template <typename>
class Node;


template <typename T, template <typename> typename Node = Node>
class BinarySearchTree
{
public:
    BinarySearchTree(
        PrintStrategy<T, Node>* = new PrintCommandLineColorlessStrategy<T>,
        const std::function<bool(const T &, const T &)> & comparator = std::less<T>()
    );
    virtual ~BinarySearchTree();

    virtual Node<T>* search(const T & key);
    virtual BinarySearchTree & insert(const T & key);
    virtual BinarySearchTree & remove(const T & key);

    Node<T>* getRoot() const;

    Node<T>* minimum(Node<T>* target) const;
    Node<T>* maximum(Node<T>* target) const;
    Node<T>* predecessor(Node<T>* target) const;
    Node<T>* successor(Node<T>* target) const;

    virtual void print() const;

protected:
    Node<T>* root;
    PrintStrategy<T, Node>* printStrat;
    std::function<bool(const T & first, const T & second)> comparator;


    void free(Node<T>* target) const;
    void swapKeys(Node<T>* first, Node<T>* second) const;
    Node<T>* searchParent(const T & key) const;
    void rotate(Node<T>* child);
};


template <typename T, template <typename> typename Node>
BinarySearchTree<T, Node>::BinarySearchTree(
    PrintStrategy<T, Node>* printStrat,
    const std::function<bool(const T &, const T &)> & comparator):
    root(nullptr),
    printStrat(printStrat),
    comparator(comparator)
{

}

template <typename T, template <typename> typename Node>
BinarySearchTree<T, Node>::~BinarySearchTree()
{
    free(root);
    delete printStrat;
}

template <typename T, template <typename> typename Node>
void BinarySearchTree<T, Node>::free(Node<T>* target) const
{
    if (!target)
        return;
    free(dynamic_cast<Node<T>*>(target->getLeft()));
    free(dynamic_cast<Node<T>*>(target->getRight()));
    delete target;
}

template <typename T, template <typename> typename Node>
void BinarySearchTree<T, Node>::swapKeys(Node<T>* first, Node<T>* second) const
{
    auto firstKey = first->getKey();
    first->setKey(second->getKey());
    second->setKey(firstKey);
}

template <typename T, template <typename> typename Node>
Node<T>* BinarySearchTree<T, Node>::minimum(Node<T>* target) const
{
    if (!target)
    {
        return nullptr;
    }
    Node<T>* result = target;
    while(target->getLeft())
    {
        return minimum(target->getLeft());
    }
    return result;
}

template <typename T, template <typename> typename Node>
Node<T>* BinarySearchTree<T, Node>::maximum(Node<T>* target) const
{
    if (!target)
    {
        return nullptr;
    }
    Node<T>* result = target;
    while(target->getRight())
    {
        return maximum(dynamic_cast<Node<T>*>(target->getRight()));
    }
    return result;
}

template <typename T, template <typename> typename Node>
Node<T>* BinarySearchTree<T, Node>::predecessor(Node<T>* target) const
{
    if (target->getLeft())
    {
        return maximum(target->getLeft());
    }
    else
    {
        Node<T>* result = target;
        while (result && result != result->getParent()->getRight())
        {
            result = result->getParent();
        }
        return result;
    }
}

template <typename T, template <typename> typename Node>
Node<T>* BinarySearchTree<T, Node>::successor(Node<T>* target) const
{
    if (target->getRight())
    {
        return minimum(target->getRight());
    }
    else
    {
        Node<T>* result = target;
        while (result && result != result->getParent()->getLeft())
        {
            result = result->getParent();
        }
        return result;
    }
}

// rotates left if child is the right child of its parent, or
// rotates right if child is the left child of its parent
template <typename T, template <typename> typename Node>
void BinarySearchTree<T, Node>::rotate(Node<T>* child)
{
    if (!child)
    {
        throw InvalidNode("Can not rotate null-node");
        return;
    }

    // short references
    bool direction = (child == child->getParent()->getLeft()); // true - rotate right, false - left
    Node<T>* parent = dynamic_cast<Node<T>*>(child->getParent());
    Node<T>* grandparent = dynamic_cast<Node<T>*>(child->getGrandparent());

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
template <typename T, template <typename> typename Node>
Node<T>* BinarySearchTree<T, Node>::searchParent(const T & key) const
{
    Node<T>* parent = nullptr;
    Node<T>* current = root;
    while (current)
    {
        parent = current;
        if (comparator(key, current->getKey()))
        {
            current = dynamic_cast<Node<T>*>(current->getLeft());
        }
        else if (comparator(current->getKey(), key))
        {
            current = dynamic_cast<Node<T>*>(current->getRight());
        }
        else
        {
            parent = dynamic_cast<Node<T>*>(parent->getParent());
            break;
        }
    }
    return parent;
}

template <typename T, template <typename> typename Node>
Node<T>* BinarySearchTree<T, Node>::search(const T & key)
{
    Node<T>* current = root;
    while (current)
    {
        if (comparator(key, current->getKey()))
        {
            current = dynamic_cast<Node<T>*>(current->getLeft());
        }
        else if (comparator(current->getKey(), key))
        {
            current = dynamic_cast<Node<T>*>(current->getRight());
        }
        else
        {
            return current;
        }
    }
    return nullptr;
}

template <typename T, template <typename> typename Node>
BinarySearchTree<T, Node> & BinarySearchTree<T, Node>::insert(const T & key)
{
    Node<T>* found = search(key);
    if (!found) // duplicates are not allowed
    {
        Node<T>* toBeInserted = new Node<T>(key);
        if (!root)
        {
            root = toBeInserted;
            return (*this);
        }
        Node<T>* parent = searchParent(key);

        // parent can't be nullptr, cause then we would have exited the function earlier on
        (comparator(key, parent->getKey())) ? parent->setLeft(toBeInserted) : parent->setRight(toBeInserted);
        toBeInserted->setParent(parent);
    }
    return (*this);
}

template <typename T, template <typename> typename Node>
BinarySearchTree<T, Node> & BinarySearchTree<T, Node>::remove(const T & key)
{
    Node<T>* found = search(key);
    if (!found)
    {
        throw AbsentKey("Can not remove absent key");
        return (*this);
    }

    Node<T>* toBeRemoved = found;
    // set toBeRemoved to be found's predecessor if any
    if (toBeRemoved->getLeft())
    {
        toBeRemoved = maximum(dynamic_cast<Node<T>*>(toBeRemoved->getLeft()));
    }
    auto parent = toBeRemoved->getParent();
    // child is only non-null child of toBeRemoved if any
    auto child = dynamic_cast<Node<T>*>(
                     (toBeRemoved->getLeft()) ? toBeRemoved->getLeft() : toBeRemoved->getRight());

    if (root != toBeRemoved)
    {
        (toBeRemoved == parent->getRight()) ? parent->setRight(child) : parent->setLeft(child);
        swapKeys(toBeRemoved, found);
    }
    else
    {
        root = child;
    }
    if (child)
        child->setParent(parent);

    delete toBeRemoved;
    return (*this);
}

template <typename T, template <typename> typename Node>
void BinarySearchTree<T, Node>::print() const
{
    printStrat->print(*this);
}

template <typename T, template <typename> typename Node>
Node<T>* BinarySearchTree<T, Node>::getRoot() const
{
    return root;
}
}

#endif // BINARYSEARCHTREE_H
