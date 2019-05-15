#ifndef REDBLACKTREEIMPL_H
#define REDBLACKTREEIMPL_H

#include <BinarySearchTreeImpl.h>
#include <TreeType.h>

namespace bst
{
    template <typename, typename>
    class BinarySearchTreeImpl;

    template <typename K, typename V>
    class RedBlackTreeImpl : public BinarySearchTreeImpl<K, V>
    {
    public:
        RedBlackTreeImpl() {}
        virtual ~RedBlackTreeImpl() {}

        virtual void insert(Node<K, V>* & root, const K & key, const V & value) const override;
        virtual void remove(Node<K, V>* & root, const K & key) const override;

        virtual const TreeType getType() const override;

    protected:
        void insertCase1(Node<K, V>* & root, Node<K, V>* current) const;
        void insertCase2(Node<K, V>* & root, Node<K, V>* current) const;
        void insertCase3(Node<K, V>* & root, Node<K, V>* current) const;
        void insertCase4(Node<K, V>* & root, Node<K, V>* current) const;

        void removeCase1(Node<K, V>* & root, Node<K, V>* current) const;
        void removeCase2(Node<K, V>* & root, Node<K, V>* current) const;
        void removeCase3(Node<K, V>* & root, Node<K, V>* current) const;
        void removeCase4(Node<K, V>* & root, Node<K, V>* current) const;
        void removeCase5(Node<K, V>* & root, Node<K, V>* current) const;
        void removeCase6(Node<K, V>* & root, Node<K, V>* current) const;

        void replace(Node<K, V>* & root, Node<K, V>* first, Node<K, V>* second) const;
        void swapColors(Node<K, V>* first, Node<K, V>* second) const;

        const bool isRed(const Node<K, V>* target) const;
        const bool isBlack(const Node<K, V>* target) const;
    };


    template <typename K, typename V>
    void RedBlackTreeImpl<K, V>::swapColors(Node<K, V>* first, Node<K, V>* second) const
    {
        auto firstColor = first->getColor();
        first->setColor(second->getColor());
        second->setColor(firstColor);
    }

    template <typename K, typename V>
    void RedBlackTreeImpl<K, V>::replace(Node<K, V>* & root, Node<K, V>* first, Node<K, V>* second) const
    {
        if (first)
        {
            if (root == first)
            {
                root = second;
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

    template <typename K, typename V>
    void RedBlackTreeImpl<K, V>::insert(Node<K, V>* & root, const K & key, const V & value) const
    {
        auto toBeInserted = Node<K, V>::createRed(key, value);
        auto current = root;
        Node<K, V>* parent = nullptr;
        while (current)
        {
            parent = current;
            if (toBeInserted->getKey() < current->getKey())
            {
                current = current->getLeft();
            }
            else if (toBeInserted->getKey() > current->getKey())
            {
                current = current->getRight();
            }
            else
            {
                return; // no duplicates allowed
            }
        }

        toBeInserted->setParent(parent);

        insertCase1(root, toBeInserted);
    }

    // current node is root
    template <typename K, typename V>
    void RedBlackTreeImpl<K, V>::insertCase1(Node<K, V>* & root, Node<K, V>* current) const
    {
        auto parent = current->getParent();
        if (parent == nullptr)
        {
            current->setColor(Color::black);
            root = current;
        }
        else
        {
            (current->getKey() < parent->getKey()) ? parent->setLeft(current) : parent->setRight(current);
            insertCase2(root, current);
        }
    }

    // parent is red, uncle is red (if parent is black then the tree is still valid)
    template <typename K, typename V>
    void RedBlackTreeImpl<K, V>::insertCase2(Node<K, V>* & root, Node<K, V>* current) const
    {
        // short references
        auto parent = current->getParent();
        auto grandparent = current->getGrandparent();
        auto uncle = current->getUncle();

        if (parent->getColor() == Color::red)
        {
            if (uncle && uncle->getColor() == Color::red)
            {
                parent->setColor(Color::black);
                uncle->setColor(Color::black);
                grandparent->setColor(Color::red);
                insertCase1(root, grandparent);
            }
            else
            {
                insertCase3(root, current);
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
    template <typename K, typename V>
    void RedBlackTreeImpl<K, V>::insertCase3(Node<K, V>* & root, Node<K, V>* current) const
    {
        // short references
        auto parent = current->getParent();
        auto grandparent = current->getGrandparent();

        if (current == parent->getLeft() && parent == grandparent->getRight())
        {
            BinarySearchTreeImpl<K, V>::rotate(root, current);
            current = parent;
        }
        else if (current == parent->getRight() && parent == grandparent->getLeft())
        {
            BinarySearchTreeImpl<K, V>::rotate(root, current);
            current = parent;
        }
        insertCase4(root, current);
    }

    // parent is red, uncle is black, also
    // current is left child of parent and parent is left child of grandparent or
    // current is right child of parent and parent is right child of grandparent
    template <typename K, typename V>
    void RedBlackTreeImpl<K, V>::insertCase4(Node<K, V>* & root, Node<K, V>* current) const
    {
        // short references
        auto parent = current->getParent();
        auto grandparent = current->getGrandparent();

        parent->setColor(Color::black);
        grandparent->setColor(Color::red);
        BinarySearchTreeImpl<K, V>::rotate(root, parent);
    }

    template <typename K, typename V>
    void RedBlackTreeImpl<K, V>::remove(Node<K, V>* & root, const K & key) const
    {
        Node<K, V>* toBeDeleted = BinarySearchTreeImpl<K, V>::search(root, key);
        Node<K, V>* substitute;

        // node with a given key wasn't found in the tree
        if (!toBeDeleted)
        {
            throw AbsentKey("Can not remove absent key");
            return;
        }

        // equivalent to calling predecessor() on toBeDeleted only if
        // the left subtree is not empty
        if (toBeDeleted->getLeft())
        {
            substitute = BinarySearchTreeImpl<K, V>::maximum(toBeDeleted->getLeft());
            BinarySearchTreeImpl<K, V>::swapKeys(substitute, toBeDeleted);
            BinarySearchTreeImpl<K, V>::swapValues(substitute, toBeDeleted);
        }
        // if both left and right subtree is empty then no substitution is needed
        else
        {
            substitute = toBeDeleted;
        }

        // substitute can't have two non-null children, thus child is either the only non-null
        // child of its parent or null child if both children are nulls
        auto child = (substitute->getLeft()) ?substitute->getLeft() : substitute->getRight();

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
                removeCase1(root, substitute);
            }
        }

        // if substitute is red then both its children are black and replacing
        // substitute with child seals the deal straight away
        replace(root, substitute, child);

        delete substitute;
    }

    // case of deleting the root: current becomes new root in result of swap method,
    // thus in this case everything is already done and we can safely delete ex-root
    template <typename K, typename V>
    void RedBlackTreeImpl<K, V>::removeCase1(Node<K, V>* & root, Node<K, V>* current) const
    {
        if (root != current)
        {
            // NOTE: in the following cases parent can't be null due to the if statement above
            removeCase2(root, current);
        }
    }

    // sibling is red, sibling's children are black
    template <typename K, typename V>
    void RedBlackTreeImpl<K, V>::removeCase2(Node<K, V>* & root, Node<K, V>* current) const
    {
        // short references
        auto parent = current->getParent();
        auto sibling = current->getSibling();

        if (isRed(sibling))
        {
            // paint sibling black and parent red
            swapColors(sibling, parent);
            BinarySearchTreeImpl<K, V>::rotate(root, sibling);
        }
        removeCase3(root, current);
    }

    // parent is black, sibling is black, sibling's children are black
    template <typename K, typename V>
    void RedBlackTreeImpl<K, V>::removeCase3(Node<K, V>* & root, Node<K, V>* current) const
    {
        // short references
        auto parent = current->getParent();
        auto sibling = current->getSibling();

        if (isBlack(parent) && isBlack(sibling) &&
                isBlack(sibling->getLeft()) && isBlack(sibling->getRight()))
        {
            sibling->setColor(Color::red);
            removeCase1(root, parent);
        }
        else
        {
            removeCase4(root, current);
        }
    }

    // parent is red, sibling is black, sibling's children are black
    template <typename K, typename V>
    void RedBlackTreeImpl<K, V>::removeCase4(Node<K, V>* & root, Node<K, V>* current) const
    {
        // short references
        auto parent = current->getParent();
        auto sibling = current->getSibling();

        if (isRed(parent) && isBlack(sibling) &&
                isBlack(sibling->getLeft()) && isBlack(sibling->getRight()))
        {
            // paint sibling red and parent black
            swapColors(sibling, parent);
        }
        else
        {
            removeCase5(root, current);
        }
    }

    // 1) sibling is black, current is the left child of its parent,
    // left sibling's child is red, right sibling's child is black
    // OR
    // 2) sibling is black, current is the right child of its parent
    // right sibling's child is red, left sibling's child is black.
    template <typename K, typename V>
    void RedBlackTreeImpl<K, V>::removeCase5(Node<K, V>* & root, Node<K, V>* current) const
    {
        // short references
        auto parent = current->getParent();
        auto sibling = current->getSibling();

        // NOTE: sibling is black due to the removeCase2, no check is needed,
        // also in the following 2 cases left child has to be red, otherwise
        // we would have exited the remove method on the previous stages
        if (current == parent->getLeft() && isBlack(sibling->getRight()))
        {
            // paint sibling red and its left child black
            swapColors(sibling, sibling->getLeft());
            BinarySearchTreeImpl<K, V>::rotate(root, sibling->getLeft());
        }
        else if (current == parent->getRight() && isBlack(sibling->getRight()))
        {
            // paint sibling red and its right child black
            swapColors(sibling, sibling->getRight());
            BinarySearchTreeImpl<K, V>::rotate(root, sibling->getRight());
        }
        removeCase6(root, current);
    }

    // 1) sibling is black, current is the left child of its parent, right sibling's child is red
    // OR
    // 2) sibling is black, current is the right child of its parent, left sibling's child is red.
    template <typename K, typename V>
    void RedBlackTreeImpl<K, V>::removeCase6(Node<K, V>* & root, Node<K, V>* current) const
    {
        // short references
        auto parent = current->getParent();
        auto sibling = current->getSibling();

        sibling->setColor(parent->getColor());
        parent->setColor(Color::black);
        if (current == parent->getLeft())
        {
            sibling->getRight()->setColor(Color::black);
        }
        else // current is right child of parent
        {
            sibling->getLeft()->setColor(Color::black);
        }
        BinarySearchTreeImpl<K, V>::rotate(root, sibling);
    }

    template <typename K, typename V>
    const bool RedBlackTreeImpl<K, V>::isRed(const Node<K, V>* target) const
    {
        return (target && target->getColor() == Color::red);
    }

    template <typename K, typename V>
    const bool RedBlackTreeImpl<K, V>::isBlack(const Node<K, V>* target) const
    {
        return (!target || target->getColor() == Color::black);
    }

    template <typename K, typename V>
    inline const TreeType RedBlackTreeImpl<K, V>::getType() const
    {
        return TreeType::redBlackTree;
    }
}

#endif // REDBLACKTREEIMPL_H
