#ifndef SIMPLEMAP_H
#define SIMPLEMAP_H

#include "MapInterface.h"


namespace advalg
{
template <typename K, typename V>
class SimpleMap : public MapInterface<K, V>
{
public:
    SimpleMap(MapImplInterface<K, V>* impl):
        MapInterface<K, V>(impl)
    {

    }
    virtual ~SimpleMap() {}

    virtual SimpleMap & insert(const K & key, const V & value) override
    {
        MapInterface<K, V>::impl->insert(key, value);
        return (*this);
    }

    virtual SimpleMap & remove(const K & key) override
    {
        MapInterface<K, V>::impl->remove(key);
        return (*this);
    }

    virtual slc::List<std::pair<K, V> > getKeyValuePairs() const override
    {
        return MapInterface<K, V>::impl->getKeyValuePairs();
    }

    virtual slc::List<K> getKeys() const override
    {
        return MapInterface<K, V>::impl->getKeys();
    }

    virtual slc::List<V> getValues() const override
    {
        return MapInterface<K, V>::impl->getValues();
    }

    virtual const V* operator[](const K & key) override
    {
        return (*MapInterface<K, V>::impl)[key];
    }
};
}

#endif // SIMPLEMAP_H
