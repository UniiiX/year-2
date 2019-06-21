#ifndef ORDEREDLIST_H
#define ORDEREDLIST_H

#include <functional>

#include "List.h"

namespace slc
{
template <typename T>
class OrderedList : public List<T>
{
public:
    OrderedList(const std::function<bool(const T &, const T&)> & comparator = std::less<T>()):
        comparator(comparator)
    {

    }
    virtual ~OrderedList() {}

    virtual OrderedList<T> & append(const T & data) override
    {
        auto current = List<T>::begin;
        if (!current)
        {
            List<T>::append(data);
            return (*this);
        }
        size_t index = 0;
        while (index < List<T>::size && comparator(current->data, data))
        {
            index++;
            current = current->next;
        }
        List<T>::insert(data, index);
        return (*this);
    }

    virtual OrderedList<T> & insert(const T & data, const size_t index) override
    {
        append(data);
        return (*this);
    }

protected:
    std::function<bool(const T & first, const T & second)> comparator;
};
}

#endif // ORDEREDLIST_H
