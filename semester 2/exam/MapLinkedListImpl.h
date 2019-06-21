#ifndef MAPLINKEDLISTIMPL_H
#define MAPLINKEDLISTIMPL_H

#include "MapImplInterface.h"
#include "OrderedList.h"


namespace advalg
{
template <typename K, typename V>
class MapLinkedListImpl : public MapImplInterface<K, V>
{
public:
    MapLinkedListImpl():
        items([](const std::pair<K, V> & first, const std::pair<K, V> & second)->bool
            {
                return first.first < second.first;
            })
    {

    }
    virtual ~MapLinkedListImpl() {}

    virtual void insert(const K & key, const V & value) override
    {
        items.append(std::pair<K, V>(key, value));
    }

    virtual void remove(const K & key) override
    {
        for (size_t i = 0; i < items.getSize(); i++)
        {
            if (items[i]->first == key)
            {
                items.remove(i);
                return;
            }
        }
    }

    virtual slc::List<std::pair<K, V> > getKeyValuePairs() const override
    {
        return items;
    }

    virtual slc::List<K> getKeys() const override
    {
        slc::List<K> result;
        for (size_t i = 0; i < items.getSize(); i++)
        {
            result.append(items[i]->first);
        }
        return result;
    }

    virtual slc::List<V> getValues() const override
    {
        slc::List<K> result;
        for (size_t i = 0; i < items.getSize(); i++)
        {
            result.append(items[i]->second);
        }
        return result;
    }

    virtual V* operator[](const K & key) override
    {
        for (size_t i = 0; i < items.getSize(); i++)
        {
            if (items[i]->first == key)
            {
                return &items[i]->second;
            }
        }
        return nullptr;
    }

protected:
    slc::OrderedList<std::pair<K, V> > items;
};
}

#endif // MAPLINKEDLISTIMPL_H
