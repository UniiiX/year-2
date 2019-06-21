#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include "BinarySearchTree.h"
#include "RedBlackNode.h"
#include "PrintCommandLineColorfulStrategy.h"

namespace bst
{
template <typename, template <typename> typename>
class BinarySearchTree;

template <typename>
class PrintCommandLineColorfulStrategy;


template <typename T>
class RedBlackTree : public BinarySearchTree<T, RedBlackNode>
{
public:
    RedBlackTree(const std::function<bool(const T &, const T &)> & comparator = std::less<T>());
    virtual ~RedBlackTree() {}

    virtual RedBlackTree<T>& insert(const T & key) override;
    virtual RedBlackTree<T>& remove(const T & key) override;

protected:
    void insertCase1(RedBlackNode<T>* current);
    void insertCase2(RedBlackNode<T>* current);
    void insertCase3(RedBlackNode<T>* current);
    void insertCase4(RedBlackNode<T>* current);

    void removeCase1(RedBlackNode<T>* current);
    void removeCase2(RedBlackNode<T>* current);
    void removeCase3(RedBlackNode<T>* current);
    void removeCase4(RedBlackNode<T>* current);
    void removeCase5(RedBlackNode<T>* current);
    void removeCase6(RedBlackNode<T>* current);

    void replace(RedBlackNode<T>* first, RedBlackNode<T>* second);
    void swapColors(RedBlackNode<T>* first, RedBlackNode<T>* second) const;

    static const bool isRed(const RedBlackNode<T>* target);
    static const bool isBlack(const RedBlackNode<T>* target);
};


template <typename T>
RedBlackTree<T>::RedBlackTree(const std::function<bool(const T &, const T &)> & comparator):
    BinarySearchTree<T, RedBlackNode>(new PrintCommandLineColorfulStrategy<T>, comparator)
{

}

template <typename T>
void RedBlackTree<T>::swapColors(RedBlackNode<T>* first, RedBlackNode<T>* second) const
{
    auto firstColor = first->getColor();
    first->setColor(second->getColor());
    second->setColor(firstColor);
}

template <typename T>
void RedBlackTree<T>::replace(RedBlackNode<T>* first, RedBlackNode<T>* second)
{
    if (first)
    {
        if (BinarySearchTree<T, RedBlackNode>::root == first)
        {
            BinarySearchTree<T, RedBlackNode>::root = second;
        }
        else
        {
            auto parent = first->getParent();
            (first == parent->getLeft()) ? parent->setLeft(second) : parent->setRight(second);
            if (second)
                second->setParent(parent);
        }
    }
}

template <typename T>
RedBlackTree<T>& RedBlackTree<T>::insert(const T & key)
{
    auto toBeInserted = new RedBlackNode<T>(key);
    auto current = BinarySearchTree<T, RedBlackNode>::root;
    RedBlackNode<T>* parent = nullptr;
    while (current)
    {
        parent = current;
        if (toBeInserted->getKey() < current->getKey())
        {
            current = dynamic_cast<RedBlackNode<T>*>(current->getLeft());
        }
        else if (toBeInserted->getKey() > current->getKey())
        {
            current = dynamic_cast<RedBlackNode<T>*>(current->getRight());
        }
        else
        {
            return (*this); // no duplicates allowed
        }
    }

    toBeInserted->setParent(parent);

    insertCase1(toBeInserted);
    return (*this);
}

// current node is root
template <typename T>
void RedBlackTree<T>::insertCase1(RedBlackNode<T>* current)
{
    auto parent = current->getParent();
    if (parent == nullptr)
    {
        current->setColor(Color::black);
        BinarySearchTree<T, RedBlackNode>::root = current;
    }
    else
    {
        (current->getKey() < parent->getKey()) ? parent->setLeft(current) : parent->setRight(current);
        insertCase2(current);
    }
}

// parent is red, uncle is red (if parent is black then the tree is still valid)
template <typename T>
void RedBlackTree<T>::insertCase2(RedBlackNode<T>* current)
{
    // short references
    auto parent = dynamic_cast<RedBlackNode<T>*>(current->getParent());
    auto grandparent = dynamic_cast<RedBlackNode<T>*>(current->getGrandparent());
    auto uncle = dynamic_cast<RedBlackNode<T>*>(current->getUncle());

    if (parent->getColor() == Color::red)
    {
        if (uncle && uncle->getColor() == Color::red)
        {
            parent->setColor(Color::black);
            uncle->setColor(Color::black);
            grandparent->setColor(Color::red);
            insertCase1(grandparent);
        }
        else
        {
            insertCase3(current);
        }
    }
    else
    {
        // black parent means that the tree is still valid
    }
}

// parent is red, uncle is black, also
// current is left child of parent and parent is right child of grandparent or
// current is right child of parent and parent is left child of grandparent
template <typename T>
void RedBlackTree<T>::insertCase3(RedBlackNode<T>* current)
{
    // short references
    auto parent = dynamic_cast<RedBlackNode<T>*>(current->getParent());
    auto grandparent = dynamic_cast<RedBlackNode<T>*>(current->getGrandparent());

    if (current == parent->getLeft() && parent == grandparent->getRight())
    {
        BinarySearchTree<T, RedBlackNode>::rotate(current);
        current = parent;
    }
    else if (current == parent->getRight() && parent == grandparent->getLeft())
    {
        BinarySearchTree<T, RedBlackNode>::rotate(current);
        current = parent;
    }
    insertCase4(current);
}

// parent is red, uncle is black, also
// current is left child of parent and parent is left child of grandparent or
// current is right child of parent and parent is right child of grandparent
template <typename T>
void RedBlackTree<T>::insertCase4(RedBlackNode<T>* current)
{
    // short references
    auto parent = dynamic_cast<RedBlackNode<T>*>(current->getParent());
    auto grandparent = dynamic_cast<RedBlackNode<T>*>(current->getGrandparent());

    parent->setColor(Color::black);
    grandparent->setColor(Color::red);
    BinarySearchTree<T, RedBlackNode>::rotate(parent);
}

template <typename T>
RedBlackTree<T>& RedBlackTree<T>::remove(const T & key)
{
    RedBlackNode<T>* toBeDeleted = dynamic_cast<RedBlackNode<T>*>(
                                       BinarySearchTree<T, RedBlackNode>::search(key));
    RedBlackNode<T>* substitute;

    // node with a given key wasn't found in the tree
    if (!toBeDeleted)
    {
        throw AbsentKey("Can not remove absent key");
        return (*this);
    }

    // equivalent to calling predecessor() on toBeDeleted only if
    // the left subtree is not empty
    if (toBeDeleted->getLeft())
    {
        substitute = BinarySearchTree<T, RedBlackNode>::
                     maximum(dynamic_cast<RedBlackNode<T>*>(toBeDeleted->getLeft()));
        BinarySearchTree<T, RedBlackNode>::swapKeys(substitute, toBeDeleted);
    }
    // if both left and right subtree is empty then no substitution is needed
    else
    {
        substitute = toBeDeleted;
    }

    // substitute can't have two non-null children, thus child is either the only non-null
    // child of its parent or null child if both children are nulls
    auto child = dynamic_cast<RedBlackNode<T>*>(
                     (substitute->getLeft()) ? substitute->getLeft() : substitute->getRight());

    if (isBlack(substitute))
    {
        // if substitute is black and child is red we can free substitute
        // after painting child black, thus maintaining the red-black balance
        if (isRed(child))
        {
            child->setColor(Color::black);
        }
        // substitute is black and its child is black
        else
        {
            removeCase1(substitute);
        }
    }

    // if substitute is red then both its children are black and replacing
    // substitute with child seals the deal straight away
    replace(substitute, child);

    delete substitute;
    return (*this);
}

// case of deleting the root: current becomes new root in result of swap method,
// thus in this case everything is already done and we can safely delete ex-root
template <typename T>
void RedBlackTree<T>::removeCase1(RedBlackNode<T>* current)
{
    if (BinarySearchTree<T, RedBlackNode>::root != current)
    {
        // NOTE: in the following cases parent can't be null due to the if statement above
        removeCase2(current);
    }
}

// sibling is red, sibling's children are black
template <typename T>
void RedBlackTree<T>::removeCase2(RedBlackNode<T>* current)
{
    // short references
    auto parent = dynamic_cast<RedBlackNode<T>*>(current->getParent());
    auto sibling = dynamic_cast<RedBlackNode<T>*>(current->getSibling());

    if (isRed(sibling))
    {
        // paint sibling black and parent red
        swapColors(sibling, parent);
        BinarySearchTree<T, RedBlackNode>::rotate(sibling);
    }
    removeCase3(current);
}

// parent is black, sibling is black, sibling's children are black
template <typename T>
void RedBlackTree<T>::removeCase3(RedBlackNode<T>* current)
{
    // short references
    auto parent = dynamic_cast<RedBlackNode<T>*>(current->getParent());
    auto sibling = dynamic_cast<RedBlackNode<T>*>(current->getSibling());

    if (isBlack(parent) &&
            isBlack(sibling) &&
            isBlack(dynamic_cast<RedBlackNode<T>*>(sibling->getLeft())) &&
            isBlack(dynamic_cast<RedBlackNode<T>*>(sibling->getRight())))
    {
        sibling->setColor(Color::red);
        removeCase1(parent);
    }
    else
    {
        removeCase4(current);
    }
}

// parent is red, sibling is black, sibling's children are black
template <typename T>
void RedBlackTree<T>::removeCase4(RedBlackNode<T>* current)
{
    // short references
    auto parent = dynamic_cast<RedBlackNode<T>*>(current->getParent());
    auto sibling = dynamic_cast<RedBlackNode<T>*>(current->getSibling());

    if (isRed(parent) &&
            isBlack(sibling) &&
            isBlack(dynamic_cast<RedBlackNode<T>*>(sibling->getLeft())) &&
            isBlack(dynamic_cast<RedBlackNode<T>*>(sibling->getRight())))
    {
        // paint sibling red and parent black
        swapColors(sibling, parent);
    }
    else
    {
        removeCase5(current);
    }
}

// 1) sibling is black, current is the left child of its parent,
// left sibling's child is red, right sibling's child is black
// OR
// 2) sibling is black, current is the right child of its parent
// right sibling's child is red, left sibling's child is black.
template <typename T>
void RedBlackTree<T>::removeCase5(RedBlackNode<T>* current)
{
    // short references
    auto parent = dynamic_cast<RedBlackNode<T>*>(current->getParent());
    auto sibling = dynamic_cast<RedBlackNode<T>*>(current->getSibling());

    // NOTE: sibling is black due to the removeCase2, no check is needed,
    // also in the following 2 cases left child has to be red, otherwise
    // we would have exited the remove method on the previous stages
    if (current == dynamic_cast<RedBlackNode<T>*>(parent->getLeft()) &&
            isBlack(dynamic_cast<RedBlackNode<T>*>(sibling->getRight())))
    {
        // paint sibling red and its left child black
        swapColors(sibling, dynamic_cast<RedBlackNode<T>*>(sibling->getLeft()));
        BinarySearchTree<T, RedBlackNode>::rotate(dynamic_cast<RedBlackNode<T>*>(sibling->getLeft()));
    }
    else if (current == dynamic_cast<RedBlackNode<T>*>(parent->getRight()) &&
             isBlack(dynamic_cast<RedBlackNode<T>*>(sibling->getLeft())))
    {
        // paint sibling red and its right child black
        swapColors(sibling, dynamic_cast<RedBlackNode<T>*>(sibling->getRight()));
        BinarySearchTree<T, RedBlackNode>::rotate(dynamic_cast<RedBlackNode<T>*>(sibling->getRight()));
    }
    removeCase6(current);
}

// 1) sibling is black, current is the left child of its parent, right sibling's child is red
// OR
// 2) sibling is black, current is the right child of its parent, left sibling's child is red.
template <typename T>
void RedBlackTree<T>::removeCase6(RedBlackNode<T>* current)
{
    // short references
    auto parent = dynamic_cast<RedBlackNode<T>*>(current->getParent());
    auto sibling = dynamic_cast<RedBlackNode<T>*>(current->getSibling());

    sibling->setColor(parent->getColor());
    parent->setColor(Color::black);
    if (current == parent->getLeft())
    {
        dynamic_cast<RedBlackNode<T>*>(sibling->getRight())->setColor(Color::black);
    }
    else // current is right child of parent
    {
        dynamic_cast<RedBlackNode<T>*>(sibling->getLeft())->setColor(Color::black);
    }
    BinarySearchTree<T, RedBlackNode>::rotate(sibling);
}

template <typename T>
const bool RedBlackTree<T>::isRed(const RedBlackNode<T>* target)
{
    return (target && target->getColor() == Color::red);
}

template <typename T>
const bool RedBlackTree<T>::isBlack(const RedBlackNode<T>* target)
{
    return (!target || target->getColor() == Color::black);
}
}

#endif // REDBLACKTREE_H
