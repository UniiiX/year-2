#ifndef SETREDBLACKTREEIMPL_H
#define SETREDBLACKTREEIMPL_H

#include "SetImplInterface.h"
#include "RedBlackTree.h"

namespace advalg
{
template <typename K>
class SetRedBlackTreeImpl : public SetImplInterface<K>
{
public:
    SetRedBlackTreeImpl() {}
    virtual ~SetRedBlackTreeImpl() {}

    virtual bool belongs(const K & key) override
    {
        return (items.search(key)) ? true : false;
    }

    virtual void insert(const K & key) override
    {
        items.insert(key);
    }

    virtual void remove(const K & key) override
    {
        items.remove(key);
    }

protected:
    bst::RedBlackTree<K> items;
};
}

#endif // SETREDBLACKTREEIMPL_H
