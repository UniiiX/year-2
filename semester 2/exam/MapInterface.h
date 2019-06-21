#ifndef MAPINTERFACE_H
#define MAPINTERFACE_H

#include <functional>

#include "List.h"
#include "MapImplInterface.h"

namespace advalg
{
template <typename K, typename V>
class MapInterface
{
public:
    MapInterface(MapImplInterface<K, V>* impl):
        impl(impl)
    {

    }
    virtual ~MapInterface()
    {
        delete impl;
    }

    virtual MapInterface & insert(const K & key, const V & value) = 0;
    virtual MapInterface & remove(const K & key) = 0;
    virtual slc::List<std::pair<K, V> > getKeyValuePairs() const = 0;
    virtual slc::List<K> getKeys() const = 0;
    virtual slc::List<V> getValues() const = 0;
    virtual const V* operator[](const K & key) = 0;

protected:
    MapImplInterface<K, V>* impl;
};
}

#endif // MAPINTERFACE_H
