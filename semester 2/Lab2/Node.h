#ifndef NODE_H
#define NODE_H

#include <Color.h>
#include <BinarySearchTree.h>


namespace bst
{
    template <typename, typename>
    class NodeFactory;

    template <typename K, typename V>
    class Node
    {
        friend class NodeFactory<K, V>;

    public:
        static Node* createColorless(
            const K & key,
            const V & value,
            Node* parent = nullptr,
            Node* left = nullptr,
            Node* right = nullptr);

        static Node* createRed(
            const K & key,
            const V & value,
            Node* parent = nullptr,
            Node* left = nullptr,
            Node* right = nullptr);

        static Node* createBlack(
            const K & key,
            const V & value,
            Node* parent = nullptr,
            Node* left = nullptr,
            Node* right = nullptr);


        virtual ~Node() {}

        const K & getKey() const;
        const V & getValue() const;
        Node* getLeft() const;
        Node* getRight() const;
        Node* getParent() const;
        const Color & getColor() const;

        Node* getGrandparent() const;
        Node* getUncle() const;
        Node* getSibling() const;

        void setLeft(Node* left);
        void setRight(Node* right);
        void setParent(Node* parent);
        void setKey(const K & key);
        void setValue(const V & value);
        void setColor(const Color & color);

        void setGrandparent(Node* grandparent);
        void setUncle(Node* uncle);
        void setSibling(Node* sibling);


        static void freeConnectedComponent(Node* target);


    private:
        Node* parent;
        Node* left;
        Node* right;
        K key;
        V value;
        Color color;

        Node(const K & key,
             const V & value,
             Node* parent,
             Node* left,
             Node* right,
             Color color);
    };


    template <typename K, typename V>
    inline Node<K, V>* Node<K, V>::createColorless(
        const K & key,
        const V & value,
        Node<K, V>* parent,
        Node<K, V>* left,
        Node<K, V>* right)
    {
        return new Node<K, V>(key, value, parent, left, right, Color::none);
    }

    template <typename K, typename V>
    inline Node<K, V>* Node<K, V>::createRed(
        const K & key,
        const V & value,
        Node<K, V>* parent,
        Node<K, V>* left,
        Node<K, V>* right)
    {
        return new Node<K, V>(key, value, parent, left, right, Color::red);
    }

    template <typename K, typename V>
    inline Node<K, V>* Node<K, V>::createBlack(
        const K & key,
        const V & value,
        Node<K, V>* parent,
        Node<K, V>* left,
        Node<K, V>* right)
    {
        return new Node<K, V>(key, value, parent, left, right, Color::black);
    }

    template <typename K, typename V>
    inline Node<K, V>::Node(const K & key,
                            const V & value,
                            Node* parent,
                            Node* left,
                            Node* right,
                            Color color):
        parent(parent),
        left(left),
        right(right),
        key(key),
        value(value),
        color(color)
    {

    }

    template <typename K, typename V>
    inline const K & Node<K, V>::getKey() const
    {
        return key;
    }

    template <typename K, typename V>
    inline const V & Node<K, V>::getValue() const
    {
        return value;
    }

    template <typename K, typename V>
    inline Node<K, V>* Node<K, V>::getLeft() const
    {
        return left;
    }

    template <typename K, typename V>
    inline Node<K, V>* Node<K, V>::getRight() const
    {
        return right;
    }

    template <typename K, typename V>
    inline Node<K, V>* Node<K, V>::getParent() const
    {
        return parent;
    }

    template <typename K, typename V>
    inline const Color & Node<K, V>::getColor() const
    {
        return color;
    }

    template <typename K, typename V>
    inline Node<K, V>* Node<K, V>::getGrandparent() const
    {
        if (parent)
        {
            return parent->parent;
        }
        return nullptr;
    }

    template <typename K, typename V>
    inline Node<K, V>* Node<K, V>::getUncle() const
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

    template <typename K, typename V>
    inline Node<K, V>* Node<K, V>::getSibling() const
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

    template <typename K, typename V>
    inline void Node<K, V>::setLeft(Node* left)
    {
        this->left = left;
    }

    template <typename K, typename V>
    inline void Node<K, V>::setRight(Node* right)
    {
        this->right = right;
    }

    template <typename K, typename V>
    inline void Node<K, V>::setParent(Node* parent)
    {
        this->parent = parent;
    }

    template <typename K, typename V>
    inline void Node<K, V>::setKey(const K & key)
    {
        this->key = key;
    }

    template <typename K, typename V>
    inline void Node<K, V>::setValue(const V & value)
    {
        this->value = value;
    }

    template <typename K, typename V>
    inline void Node<K, V>::setColor(const Color & color)
    {
        this->color = color;
    }

    template <typename K, typename V>
    inline void Node<K, V>::setGrandparent(Node* grandparent)
    {
        this->value = value;
    }

    template <typename K, typename V>
    inline void Node<K, V>::setUncle(Node* uncle)
    {
        this->value = value;
    }

    template <typename K, typename V>
    inline void Node<K, V>::setSibling(Node* sibling)
    {
        this->value = value;
    }

    template <typename K, typename V>
    void Node<K, V>::freeConnectedComponent(Node* target)
    {
        if (!target) return;
        freeConnectedComponent(target->left);
        freeConnectedComponent(target->right);
        delete target;
    }
}
#endif // NODE_H
