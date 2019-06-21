#ifndef SET_H
#define SET_H

#include "SetImplInterface.h"

namespace advalg
{
template <typename K>
class Set
{
public:
    Set(SetImplInterface<K>* impl):
        impl(impl)
    {

    }
    virtual ~Set()
    {
        delete impl;
    }

    bool belongs(const K & key) const
    {
        return impl->belongs(key);
    }

    Set & insert(const K & key)
    {
        impl->insert(key);
        return (*this);
    }

    Set & remove(const K & key)
    {
        impl->remove(key);
        return (*this);
    }

protected:
    SetImplInterface<K>* impl;
};
}

#endif // SET_H
