#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <cassert>
#include <iostream>


template <typename K, typename V>
class SplayTree
{
private:
    struct Node
    {
        Node* left;
        Node* right;
        Node* parent;
        K key;
        V value;

        Node(const K & key, const V & value):
             key(key),
             value(value),
             left(nullptr),
             right(nullptr),
             parent(nullptr)
             {

             }
    };

    Node* root;

    Node* minimum(Node* root) const;
    Node* maximum(Node* root) const;
    Node* predecessor(Node* target) const;
    Node* successor(Node* target) const;

    void zig(Node* pivot);

    Node* searchUtility(const K & key) const;

    void splay(Node* pivot);
    Node* split(const K & key);
    void merge(Node* otherRoot);

    void print(Node* root, std::string indent = "") const;

    void free(Node* root);

public:
    SplayTree(Node* root = nullptr);
    virtual ~SplayTree();

    Node* search(const K & key);
    void insert(const K & key, const V & value);
    void remove(const K & key);

    void print() const;
};

//======================================================================================================

template <typename K, typename V>
SplayTree<K, V>::SplayTree(Node* root) :
    root(root)
{

}

template <typename K, typename V>
SplayTree<K, V>::~SplayTree()
{
    free(root);
}

template <typename K, typename V>
void SplayTree<K, V>::free(Node* root)
{
    if (!root)
    {
        return;
    }
    if (root->left)
    {
        free(root->left);
    }
    if (root->right)
    {
        free(root->right);
    }
    delete root;
}

template <typename K, typename V>
typename SplayTree<K, V>::Node* SplayTree<K, V>::minimum(Node* root) const
{
    if (!root)
    {
        return nullptr;
    }
    Node* result = root;
    while(root->left)
    {
        return minimum(root->left);
    }
    return result;
}

template <typename K, typename V>
typename SplayTree<K, V>::Node* SplayTree<K, V>::maximum(Node* root) const
{
    if (!root)
    {
        return nullptr;
    }
    Node* result = root;
    while(root->right)
    {
        return maximum(root->right);
    }
    return result;
}

template <typename K, typename V>
typename SplayTree<K, V>::Node* SplayTree<K, V>::predecessor(Node* target) const
{
    if (target->left)
    {
        return maximum(target->left);
    }
    else
    {
        Node* result = target;
        while (result && result != result->parent->right)
        {
            result = result->parent;
        }
        return result;
    }
}

template <typename K, typename V>
typename SplayTree<K, V>::Node* SplayTree<K, V>::successor(Node* target) const
{
    if (target->right)
    {
        return minimum(target->right);
    }
    else
    {
        Node* result = target;
        while (result && result != result->parent->left)
        {
            result = result->parent;
        }
        return result;
    }
}

//        P                  X
//       / \      zig       / \
//      X   C  --------->  A   P
//     / \     <---------     / \
//    A   B                  B   C
// rotates left if pivot is the right child of its parent,
// rotates right if pivot is the left child of its parent
//
//          G               X
//         / \             / \
//        P   D           A   P
//       / \     zig-zig     / \
//      X   C   --------->  B   G
//     / \      <---------     / \
//    A   B                   C   D
//
//
//          G
//         / \
//        P   D                X
//       / \     zig-zag     /   \
//      A   X   --------->  P     G
//         / \  <--------- / \   / \
//        B   C           A   B C   D
//
// NOTE: due to the implementation of zig method zig-zig and zig-zag
// both can be replaced by two consecutive calls of zig method
template <typename K, typename V>
void SplayTree<K, V>::zig(Node* pivot)
{
    assert(pivot && pivot->parent);

    // short references
    bool direction = (pivot == pivot->parent->left); // true - rotate right, false - left
    Node* parent = pivot->parent;
    Node* grandparent = parent->parent;

    if (grandparent)
    {
        (grandparent->left == parent) ? grandparent->left = pivot : grandparent->right = pivot;
    }
    else // parent was the root of the entire tree
    {
        root = pivot; // pivot becomes the new root
    }
    pivot->parent = grandparent;

    (direction) ? parent->left = pivot->right : parent->right = pivot->left;
    if (direction)
    {
        if (pivot->right)
        {
            pivot->right->parent = parent;
        }
    }
    else
    {
        if (pivot->left)
        {
            pivot->left->parent = parent;
        }
    }

    (direction) ? pivot->right = parent : pivot->left = parent;
    parent->parent = pivot;
}


template <typename K, typename V>
void SplayTree<K, V>::splay(Node* pivot)
{
    while (pivot != root)
    {
        zig(pivot);
    }
}

// splits the tree so that one part is returned by the method and the
// original object is transformed to another part of splintered tree
template <typename K, typename V>
typename SplayTree<K, V>::Node* SplayTree<K, V>::split(const K & key)
{
    if (!root)
    {
        return nullptr;
    }

    Node* pivot;
    Node* found = searchUtility(key);

    if (found)
    {
        pivot = found;
    }
    else
    {
        (successor(found)) ? pivot = successor(found) : pivot = predecessor(found);
    }

    splay(pivot);
    Node* result = root->left;
    if (result)
    {
        root->left->parent = nullptr;
        root->left = nullptr;
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
    if (!root)
    {
        root = otherRoot;
        return;
    }
    //assert(minimum(root)->key > maximum(otherRoot)->key);
    splay(minimum(root));
    root->left = otherRoot;
    otherRoot->parent = root;
}


// returns either a value of the node that has key equal to the passed one, or
// the parent of the null node where the passed key would have been placed
template <typename K, typename V>
typename SplayTree<K, V>::Node* SplayTree<K, V>::searchUtility(const K & key) const
{
    Node* parent = nullptr;
    Node* current = root;
    while (current)
    {
        parent = current;
        if (current->key > key)
        {
            current = current->left;
        }
        else if(current->key < key)
        {
            current = current->right;
        }
        else
        {
            return current;
        }
    }
    return parent;
}

template <typename K, typename V>
typename SplayTree<K, V>::Node* SplayTree<K, V>::search(const K & key)
{
    auto found = searchUtility(key);
    if (found && found->key != key)
    {
        return nullptr;
    }
    splay(found);
    return found;
}

template <typename K, typename V>
void SplayTree<K, V>::insert(const K & key, const V & value)
{
    if (search(key))
    {
        return;
    }

    Node* toBeInserted = new Node(key, value);
    if (!root)
    {
        root = toBeInserted;
        return;
    }
    Node* parent = searchUtility(key);

    toBeInserted->parent = parent;
    (parent->key > key) ? parent->left = toBeInserted : parent->right = toBeInserted;

    Node* leftSubtreeRoot = split(key);

    if (leftSubtreeRoot)
    {
        leftSubtreeRoot->parent = toBeInserted;
        toBeInserted->left = leftSubtreeRoot;
    }
}

template <typename K, typename V>
void SplayTree<K, V>::remove(const K & key)
{
    Node* toBeDeleted = searchUtility(key);
    if (!toBeDeleted)
    {
        std::cout << "Key not found!" << std::endl;
        return;
    }

    Node* leftSubtreeRoot = split(key);

    root = root->right;
    if (root)
    {
        root->parent = nullptr;
    }
    merge(leftSubtreeRoot);

    delete toBeDeleted;
}

template <typename K, typename V>
void SplayTree<K, V>::print() const
{
    print(root);
}

template <typename K, typename V>
void SplayTree<K, V>::print(Node* root, std::string indent) const
{
    if (!root)
    {
        return;
    }
    if (root->right)
    {
        print(root->right, indent + "   ");
    }
    std::cout << indent << root->key << std::endl;
    if (root->left)
    {
        print(root->left, indent + "   ");
    }
}


#endif // SPLAYTREE_H
