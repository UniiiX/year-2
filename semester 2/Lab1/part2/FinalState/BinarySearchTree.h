#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>

template <typename K, typename V>
class BinarySearchTree
{
protected:
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

    Node* searchParent(const K & key) const;
    Node* search_(const K & key) const;

    void rotate(Node* pivot);

    virtual void print(Node* root, std::string indent = "") const;


private:
    void free(Node* root);


public:
    BinarySearchTree();
    virtual ~BinarySearchTree();

    const Node* getRoot() const;

    virtual const Node* search(const K & key) const;
    virtual void insert(const K & key, const V & value);
    virtual void remove(const K & key);
    virtual void print() const;


};

template <typename K, typename V>
BinarySearchTree<K, V>::BinarySearchTree():
    root(nullptr)
{

}

template <typename K, typename V>
BinarySearchTree<K, V>::~BinarySearchTree()
{
    free(root);
}

template <typename K, typename V>
const typename BinarySearchTree<K, V>::Node* BinarySearchTree<K, V>::getRoot() const
{
    return root;
}

template <typename K, typename V>
void BinarySearchTree<K, V>::free(Node* root)
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
typename BinarySearchTree<K, V>::Node* BinarySearchTree<K, V>::minimum(Node* root) const
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
typename BinarySearchTree<K, V>::Node* BinarySearchTree<K, V>::maximum(Node* root) const
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
typename BinarySearchTree<K, V>::Node* BinarySearchTree<K, V>::predecessor(Node* target) const
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
typename BinarySearchTree<K, V>::Node* BinarySearchTree<K, V>::successor(Node* target) const
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

// rotates left if pivot is the right child of its parent, or
// rotates left if pivot is the left child of its parent
template <typename K, typename V>
void BinarySearchTree<K, V>::rotate(Node* pivot)
{
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

// returns parent of the node with given key if the key is present in the tree, or
// returns parent of the null node where given key would have been placed if it
// was present in the tree.
template <typename K, typename V>
typename BinarySearchTree<K, V>::Node* BinarySearchTree<K, V>::searchParent(const K & key) const
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
        else if (current->key < key)
        {
            current = current->right;
        }
        else
        {
            parent = parent->parent;
            break;
        }
    }
    return parent;
}

template <typename K, typename V>
typename BinarySearchTree<K, V>::Node* BinarySearchTree<K, V>::search_(const K & key) const
{
    Node* current = root;
    while (current)
    {
        if (current->key > key)
        {
            current = current->left;
        }
        else if (current->key < key)
        {
            current = current->right;
        }
        else
        {
            return current;
        }
    }
    return nullptr;
}

template <typename K, typename V>
const typename BinarySearchTree<K, V>::Node* BinarySearchTree<K, V>::search(const K & key) const
{
    return search_(key);
}

template <typename K, typename V>
void BinarySearchTree<K, V>::insert(const K & key, const V & value)
{
    Node* found = search_(key);
    if (found)
    {
        // replacing old value with new one, cause duplicate keys are not allowed
        found->value = value;
    }
    else
    {
        Node* toBeInserted = new Node(key, value);
        if (!root)
        {
            root = toBeInserted;
            return;
        }
        Node* parent = searchParent(key);
        // parent can't be nullptr, cause if it was root would have been
        // nullptr and we would have exited the function earlier on
        (parent->key > key) ? parent->left = toBeInserted : parent->right = toBeInserted;
        toBeInserted->parent = parent;
    }
}

template <typename K, typename V>
void BinarySearchTree<K, V>::remove(const K & key)
{
    Node* found = search_(key);
    if (!found)
    {
        //std::cout << "Key not found!" << std::endl;
        return;
    }
    Node* toBeRemoved = found;
    if (toBeRemoved->left)
    {
        toBeRemoved = maximum(toBeRemoved->left);
        if (toBeRemoved->left)
        {
            rotate(toBeRemoved->left);
        }
        toBeRemoved->parent->right = nullptr;
        std::swap(toBeRemoved->key, found->key);
        std::swap(toBeRemoved->value, found->value);
    }
    else if (toBeRemoved->right)
    {
        toBeRemoved = minimum(toBeRemoved->right);
        if (toBeRemoved->left)
        {
            rotate(toBeRemoved->right);
        }
        toBeRemoved->parent->left = nullptr;
        std::swap(toBeRemoved->key, found->key);
        std::swap(toBeRemoved->value, found->value);
    }
    delete toBeRemoved;
}

template <typename K, typename V>
void BinarySearchTree<K, V>::print() const
{
    print(root);
}

template <typename K, typename V>
void BinarySearchTree<K, V>::print(Node* root, std::string indent) const
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


#endif // BINARYTREE_H
