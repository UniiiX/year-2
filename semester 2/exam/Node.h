#ifndef NODE_H
#define NODE_H


namespace bst
{
template <typename T>
class Node
{
public:
    Node(const T & key,
         Node* parent = nullptr,
         Node* left = nullptr,
         Node* right = nullptr);
    virtual ~Node() {}

    const T & getKey() const;
    Node* getLeft() const;
    Node* getRight() const;
    Node* getParent() const;

    Node* getGrandparent() const;
    Node* getUncle() const;
    Node* getSibling() const;

    void setLeft(Node* left);
    void setRight(Node* right);
    void setParent(Node* parent);
    void setKey(const T & key);

    void setGrandparent(Node* grandparent);
    void setUncle(Node* uncle);
    void setSibling(Node* sibling);


protected:
    T key;
    Node* parent;
    Node* left;
    Node* right;
};

template <typename T>
inline Node<T>::Node(const T & key,
                        Node* parent,
                        Node* left,
                        Node* right):
    key(key),
    parent(parent),
    left(left),
    right(right)
{

}

template <typename T>
inline const T & Node<T>::getKey() const
{
    return key;
}

template <typename T>
inline Node<T>* Node<T>::getLeft() const
{
    return left;
}

template <typename T>
inline Node<T>* Node<T>::getRight() const
{
    return right;
}

template <typename T>
inline Node<T>* Node<T>::getParent() const
{
    return parent;
}

template <typename T>
inline Node<T>* Node<T>::getGrandparent() const
{
    if (parent)
    {
        return parent->parent;
    }
    return nullptr;
}

template <typename T>
inline Node<T>* Node<T>::getUncle() const
{
    Node* grandparent = getGrandparent();
    if (grandparent)
    {
        if (grandparent->getLeft() == parent)
        {
            return grandparent->getRight();
        }
        else
        {
            return grandparent->getLeft();
        }
    }
    return nullptr;
}

template <typename T>
inline Node<T>* Node<T>::getSibling() const
{
    if (parent)
    {
        if (parent->getLeft() == this)
        {
            return parent->getRight();
        }
        else
        {
            return parent->getLeft();
        }
    }
    return nullptr;
}

template <typename T>
inline void Node<T>::setLeft(Node* left)
{
    this->left = left;
}

template <typename T>
inline void Node<T>::setRight(Node* right)
{
    this->right = right;
}

template <typename T>
inline void Node<T>::setParent(Node* parent)
{
    this->parent = parent;
}

template <typename T>
inline void Node<T>::setKey(const T & key)
{
    this->key = key;
}

template <typename T>
inline void Node<T>::setGrandparent(Node* grandparent)
{
    this->grandparent = grandparent;
}

template <typename T>
inline void Node<T>::setUncle(Node* uncle)
{
    this->uncle = uncle;
}

template <typename T>
inline void Node<T>::setSibling(Node* sibling)
{
    this->sibling = sibling;
}
}
#endif // NODE_H
