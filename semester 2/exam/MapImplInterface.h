#ifndef MAPIMPLINTERFACE_H
#define MAPIMPLINTERFACE_H

#include "List.h"

namespace advalg
{
template <typename K, typename V>
class MapImplInterface
{
public:
    MapImplInterface() {}
    virtual ~MapImplInterface() {}

    virtual void insert(const K & key, const V & value) = 0;
    virtual void remove(const K & key) = 0;
    virtual slc::List<std::pair<K, V> > getKeyValuePairs() const = 0;
    virtual slc::List<K> getKeys() const = 0;
    virtual slc::List<V> getValues() const = 0;
    virtual const V* operator[](const K & key) = 0;
};
}

#endif // MAPIMPLINTERFACE_H
