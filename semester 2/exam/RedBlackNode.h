#ifndef REDBLACKNODE_H
#define REDBLACKNODE_H

#include "Node.h"
#include "Color.h"

namespace bst
{
template <typename T>
class RedBlackNode : public Node<T>
{
protected:
    Color color;

public:
    RedBlackNode(const T & key,
                 RedBlackNode* parent = nullptr,
                 RedBlackNode* left = nullptr,
                 RedBlackNode* right = nullptr,
                 const Color & color = Color::red);
    virtual ~RedBlackNode() {}

    const Color & getColor() const;
    void setColor(const Color & color);
};

template <typename T>
RedBlackNode<T>::RedBlackNode(const T & key,
                              RedBlackNode<T>* parent,
                              RedBlackNode<T>* left,
                              RedBlackNode<T>* right,
                              const Color & color):
    Node<T>(key, parent, left, right),
    color(color)
{

}

template <typename T>
const Color & RedBlackNode<T>::getColor() const
{
    return color;
}

template <typename T>
void RedBlackNode<T>::setColor(const Color & color)
{
    this->color = color;
}
}

#endif // REDBLACKNODE_H
