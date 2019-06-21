#ifndef SETLINKEDLISTIMPL_H
#define SETLINKEDLISTIMPL_H

#include "SetImplInterface.h"
#include "OrderedList.h"

namespace advalg
{
template <typename K>
class SetLinkedListImpl : public SetImplInterface<K>
{
public:
    SetLinkedListImpl() {}
    virtual ~SetLinkedListImpl() {}

    virtual bool belongs(const K & key) override
    {
        for (int i = 0; i < items.getSize(); ++i)
        {
            if (*items[i] == key)
            {
                return true;
            }
        }
        return false;
    }

    virtual void insert(const K & key) override
    {
        items.append(key);
    }

    virtual void remove(const K & key) override
    {
        for (int i = 0; i < items.getSize(); ++i)
        {
            if (*items[i] == key)
            {
               items.remove(i);
            }
        }
    }

protected:
    slc::OrderedList<K> items;
};
}

#endif // SETLINKEDLISTIMPL_H
