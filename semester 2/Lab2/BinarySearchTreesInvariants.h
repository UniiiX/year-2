#ifndef BINARYSEARCHTREESINVARIANTS_H
#define BINARYSEARCHTREESINVARIANTS_H

#include <BinarySearchTree.h>

namespace bst
{
    template <typename, typename>
    class BinarySearchTree;

    template <typename, typename>
    class RedBlackTreeImpl;

    template <typename K, typename V>
    class BinarySearchTreesInvariants
    {
    public:
        BinarySearchTreesInvariants() = delete;
        BinarySearchTreesInvariants(const BinarySearchTreesInvariants &) =  delete;
        BinarySearchTreesInvariants(BinarySearchTreesInvariants &&) = delete;
        virtual ~BinarySearchTreesInvariants() = delete;
        BinarySearchTreesInvariants & operator=(const BinarySearchTreesInvariants &) = delete;
        BinarySearchTreesInvariants & operator=(BinarySearchTreesInvariants &&) = delete;

        static bool obeysBinarySearchTreeInvariant(BinarySearchTree<K, V> & target);
        static bool obeysBinarySearchTreeInvariant(const Node<K, V>* target);
        static bool obeysRedBlackTreeInvariant(BinarySearchTree<K, V> & target);

        static bool rootIsBlack(BinarySearchTree<K, V> & target);
        static bool redNodeCantHaveRedChild(const Node<K, V>* target);
        static bool nodesAreEitherBlackOrRed(const Node<K, V>* target);
        static bool simplePathsBlackLengthsAreEqual(const Node<K, V>* target);
        static int calculateLeftBranchBlackHeight(const Node<K, V>* target);

        static void setRootColor(BinarySearchTree<K, V> & target, const Color & color);
    };

    template <typename K, typename V>
    bool BinarySearchTreesInvariants<K, V>::obeysBinarySearchTreeInvariant(BinarySearchTree<K, V> & target)
    {
        return obeysBinarySearchTreeInvariant(target.getRoot());
    }

    template <typename K, typename V>
    bool BinarySearchTreesInvariants<K, V>::obeysBinarySearchTreeInvariant(const Node<K, V>* target)
    {
        if (!target)
        {
            return true;
        }
        return (obeysBinarySearchTreeInvariant(target->getLeft()) &&
                obeysBinarySearchTreeInvariant(target->getRight()) &&
                (!target->getRight() || target->getKey() < target->getRight()->getKey()) &&
                (!target->getLeft() || target->getKey() > target->getLeft()->getKey()));
    }

    template <typename K, typename V>
    bool BinarySearchTreesInvariants<K, V>::obeysRedBlackTreeInvariant(BinarySearchTree<K, V> & target)
    {
        auto root = target.getRoot();
        return (obeysBinarySearchTreeInvariant(target) &&
                rootIsBlack(target) &&
                redNodeCantHaveRedChild(root) &&
                nodesAreEitherBlackOrRed(root) &&
                simplePathsBlackLengthsAreEqual(root));
    }

    template <typename K, typename V>
    bool BinarySearchTreesInvariants<K, V>::rootIsBlack(BinarySearchTree<K, V> & target)
    {
        return RedBlackTreeImpl<K, V>::isBlack(target.getRoot());
    }

    template <typename K, typename V>
    bool BinarySearchTreesInvariants<K, V>::redNodeCantHaveRedChild(const Node<K, V>* target)
    {
        if (!target)
        {
            return true;
        }
        return (RedBlackTreeImpl<K, V>::isRed(target) ?
                RedBlackTreeImpl<K, V>::isBlack(target->getLeft()) &&
                RedBlackTreeImpl<K, V>::isBlack(target->getRight()) : true &&
                redNodeCantHaveRedChild(target->getLeft()) &&
                redNodeCantHaveRedChild(target->getRight()));
    }

    template <typename K, typename V>
    bool BinarySearchTreesInvariants<K, V>::nodesAreEitherBlackOrRed(const Node<K, V>* target)
    {
        if (!target)
        {
            return true;
        }
        return ((RedBlackTreeImpl<K, V>::isBlack(target) ||
                RedBlackTreeImpl<K, V>::isRed(target)) &&
                nodesAreEitherBlackOrRed(target->getLeft()) &&
                nodesAreEitherBlackOrRed(target->getRight()));
    }

    template <typename K, typename V>
    bool BinarySearchTreesInvariants<K, V>::simplePathsBlackLengthsAreEqual(const Node<K, V>* target)
    {
        if (!target)
        {
            return true;
        }
        return (calculateLeftBranchBlackHeight(target->getLeft()) ==
                calculateLeftBranchBlackHeight(target->getRight()));
    }

    template <typename K, typename V>
    int BinarySearchTreesInvariants<K, V>::calculateLeftBranchBlackHeight(const Node<K, V>* target)
    {
        int result = 0;
        while (target)
        {
            if (RedBlackTreeImpl<K, V>::isBlack(target))
                result++;
            target = target->getLeft();
        }
        return result;
    }

    template <typename K, typename V>
    void BinarySearchTreesInvariants<K, V>::setRootColor(BinarySearchTree<K, V> & target, const Color & color)
    {
        target.root->setColor(Color::red);
    }
}

#endif // BINARYSEARCHTREESINVARIANTS_H
