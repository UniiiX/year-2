#ifndef MAPREDBLACKTREEIMPL_H
#define MAPREDBLACKTREEIMPL_H

#include "MapImplInterface.h"
#include "RedBlackTree.h"


namespace advalg
{

template <typename K, typename V>
std::ostream& operator<<(std::ostream& ostr, const std::pair<K, V> & target)
{
    ostr << "{" << target.first << ", " << target.second << "}";
    return ostr;
}


template <typename K, typename V>
class MapRedBlackTreeImpl : public MapImplInterface<K, V>
{
    typedef bst::RedBlackNode<std::pair<K, V> > Node;
    typedef std::pair<K, V> Pair;

public:
    MapRedBlackTreeImpl():
        items([](const Pair & first, const Pair & second)->bool
    {
        return first.first < second.first;
    })
    {

    }
    virtual ~MapRedBlackTreeImpl() {}

    virtual void insert(const K & key, const V & value) override
    {
        items.insert(Pair(key, value));
    }

    virtual void remove(const K & key) override
    {
        // arbitrary value is needed in order to create a pair
        // pairs are considered to be equal if comparator can
        // not define that one of them is less than other,
        // hence (in most common cases) it all depends on
        // the keys, that's why only the key is important
        V value = items.getRoot()->getKey().second;
        items.remove(Pair(key, value));
    }

    virtual slc::List<Pair> getKeyValuePairs() const override
    {
        slc::List<Pair> result;
        traverse<Pair>(items.getRoot(),
                       result,
                       [](bst::RedBlackNode<Pair>* target)->Pair
        {
            return target->getKey();
        });
        return result;
    }

    virtual slc::List<K> getKeys() const override
    {
        slc::List<K> result;
        traverse<K>(items.getRoot(),
                    result,
                    [](Node* target)
        {
            return target->getKey().first;
        });
        return result;
    }

    virtual slc::List<V> getValues() const override
    {
        slc::List<V> result;
        traverse<V>(items.getRoot(),
                    result,
                    [](Node* target)
        {
            return target->getKey().second;
        });
        return result;
    }

    virtual const V* operator[](const K & key) override
    {
        V value = items.getRoot()->getKey().second;
        // once again value is not important,
        // everything depends on the key
        Node* found = items.search(Pair(key, value));
        if (found)
        {
            return &found->getKey().second;
        }
        else
        {
            return nullptr;
        }
    }

protected:
    bst::RedBlackTree<Pair> items;

    template <typename T>
    void traverse(Node* current,
                  slc::List<T> & toBeFilled,
                  const std::function<T(Node*)> & traversalGetter) const
    {
        if (!current)
            return;
        toBeFilled.append(traversalGetter(current));
        traverse(dynamic_cast<Node*>(current->getLeft()), toBeFilled, traversalGetter);
        traverse(dynamic_cast<Node*>(current->getRight()), toBeFilled, traversalGetter);
    }
};
}

#endif // MAPREDBLACKTREEIMPL_H
