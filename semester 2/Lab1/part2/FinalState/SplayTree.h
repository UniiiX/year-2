#ifndef SPLAYTREE_H
#define SPLAYTREE_H


#include "BinarySearchTree.h"


template <typename K, typename V>
class SplayTree : public BinarySearchTree<K, V>
{
    typedef typename BinarySearchTree<K, V>::Node Node;

private:
    void splay(Node* pivot);
    Node* split(const K & key);
    void merge(Node* otherRoot);

public:
    SplayTree();
    virtual ~SplayTree();

    const Node* search(const K & key);
    void insert(const K & key, const V & value);
    void remove(const K & key);
};

//======================================================================================================

template <typename K, typename V>
SplayTree<K, V>::SplayTree()
{

}

template <typename K, typename V>
SplayTree<K, V>::~SplayTree()
{

}

template <typename K, typename V>
void SplayTree<K, V>::splay(Node* pivot)
{
    while (pivot != BinarySearchTree<K, V>::root)
    {
        BinarySearchTree<K, V>::rotate(pivot);
    }
}

// puts the node with the given key into the root by calling splay method on it
// then cuts off left child of the new root from its parent and returns it
template <typename K, typename V>
typename SplayTree<K, V>::Node* SplayTree<K, V>::split(const K & key)
{
    if (!BinarySearchTree<K, V>::root)
    {
        return nullptr;
    }

    Node* pivot;
    Node* found = BinarySearchTree<K, V>::search_(key);

    if (found)
    {
        pivot = found;
    }
    else
    {
        (BinarySearchTree<K, V>::successor(found)) ?
            pivot = BinarySearchTree<K, V>::successor(found) :
            pivot = BinarySearchTree<K, V>::predecessor(found);
    }

    splay(pivot);
    Node* result = BinarySearchTree<K, V>::root->left;
    if (result)
    {
        BinarySearchTree<K, V>::root->left->parent = nullptr;
        BinarySearchTree<K, V>::root->left = nullptr;
    }
    return result;
}

template <typename K, typename V>
void SplayTree<K, V>::merge(Node* otherRoot)
{
    if (!otherRoot)
    {
        return;
    }
    if (!BinarySearchTree<K, V>::root)
    {
        BinarySearchTree<K, V>::root = otherRoot;
        return;
    }
    //assert(minimum(root)->key > maximum(otherRoot)->key);
    splay(BinarySearchTree<K, V>::minimum(BinarySearchTree<K, V>::root));
    BinarySearchTree<K, V>::root->left = otherRoot;
    otherRoot->parent = BinarySearchTree<K, V>::root;
}

template <typename K, typename V>
const typename SplayTree<K, V>::Node* SplayTree<K, V>::search(const K & key)
{
    auto found = BinarySearchTree<K, V>::search_(key);
    if (found)
    {
        splay(found);
    }
    return found;
}

template <typename K, typename V>
void SplayTree<K, V>::insert(const K & key, const V & value)
{
    BinarySearchTree<K, V>::insert(key, value);

    Node* inserted = BinarySearchTree<K, V>::search_(key);
    Node* leftSubtreeRoot = split(key);

    if (leftSubtreeRoot)
    {
        leftSubtreeRoot->parent = inserted;
        inserted->left = leftSubtreeRoot;
    }
}

template <typename K, typename V>
void SplayTree<K, V>::remove(const K & key)
{
    Node* toBeRemoved = BinarySearchTree<K, V>::search_(key);
    if (!toBeRemoved)
    {
        //std::cout << "Key not found!" << std::endl;
        return;
    }

    Node* leftSubtreeRoot = split(key);

    BinarySearchTree<K, V>::root = BinarySearchTree<K, V>::root->right;
    if (BinarySearchTree<K, V>::root)
    {
        BinarySearchTree<K, V>::root->parent = nullptr;
    }
    merge(leftSubtreeRoot);

    delete toBeRemoved;
}

#endif // SPLAYTREE_H
