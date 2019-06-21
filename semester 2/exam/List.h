#ifndef LIST_H
#define LIST_H

#include <iostream>

#include "ListExceptions.h"

namespace slc
{
template <typename T>
class List
{
    template <typename K>
    friend std::ostream& operator<<(std::ostream& ostr, const List<K> & target);

protected:
    struct Node
    {
        T data;
        Node* next;

        Node(T data, Node* next = nullptr)
        {
            this->data = data;
            this->next = next;
        }
    };

    size_t size;
    Node* begin;
    Node* end;

public:
    List();
    virtual ~List();

    size_t getSize() const;

    virtual List<T> & append(const T & data);
    virtual List<T> & insert(const T & data, const size_t index);
    virtual List<T> & remove(const size_t index);
    T* operator[](const size_t index) const;
};

template <typename T>
List<T>::List():
    size(0),
    begin(nullptr),
    end(nullptr)
{

}

template <typename T>
List<T>::~List()
{
    Node* prev = nullptr;
    Node* current = begin;
    for (size_t i = 0; i < size; ++i)
    {
        prev = current;
        current = current->next;
        delete prev;
    }
    size = 0;
}

template <typename T>
List<T> & List<T>::append(const T & data)
{
    Node* toBeAppended = new Node(data);
    if (!begin)
    {
        begin = end = toBeAppended;
    }
    end->next = toBeAppended;
    end = toBeAppended;
    toBeAppended->next = begin; // make the list cyclic
    size++;
    return (*this);
}

// inserts element before the element with given index
template <typename T>
List<T> & List<T>::insert(const T & data, const size_t index)
{
    if (0 <= index && index <= size)
    {
        // inserting before current, after prev
        Node* current = begin;
        Node* prev = nullptr;
        for (size_t i = 0; i < index; ++i)
        {
            prev = current;
            current = current->next;
        }
        Node* toBeInserted = new Node(data, current);

        if (prev)
        {
            prev->next = toBeInserted;
            if (end == prev)
            {
                end = toBeInserted;
            }

        }
        else // insertion into the beginning of the list
        {
            begin = toBeInserted;
            if (size == 0)
            {
                end = toBeInserted;
            }
            end->next = toBeInserted; // make the list cyclic
        }
        size++;
    }
    else
    {
        throw InvalidIndex("Index is out of range. Can not insert element.");
    }
    return (*this);
}

template <typename T>
List<T> & List<T>::remove(const size_t index)
{
    if (0 <= index && index < size)
    {
        Node* toBeRemoved = begin;
        Node* prev = nullptr;
        for (size_t i = 0; i < index; ++i)
        {
            prev = toBeRemoved;
            toBeRemoved = toBeRemoved->next;
        }

        if (toBeRemoved == begin) // removal from the beginning of the list
        {
            begin = begin->next;
            end->next = begin; // make the list cyclic
        }
        if (toBeRemoved == end) // removal from the end of the list
        {
            end = prev;
        }
        if (size > 0) // otherwise there is nothing to remove from the list
        {
            if (prev)
            {
                prev->next = toBeRemoved->next;
            }
            delete toBeRemoved;
            size--;
        }
    }
    else
    {
        throw InvalidIndex("Index is out of range. Can not remove element.");
    }
    return (*this);
}
template <typename T>
T* List<T>::operator[](const size_t index) const
{
    Node* current = begin;
    if (!current)
    {
        return nullptr;
    }

    for (size_t i = 0; i < index; ++i)
    {
        current = current->next;
    }
    return &current->data;
}

template <typename T>
size_t List<T>::getSize() const
{
    return size;
}

template <typename T>
std::ostream& operator<<(std::ostream& ostr, const List<T> & target)
{
    auto current = target.begin;
    ostr << "{ ";
    for (size_t i = 0; i < target.size; ++i)
    {
        ostr << current->data;
        if (i < target.size - 1)
        {
            ostr << ", ";
        }
        current = current->next;
    }
    ostr << " }";
    return ostr;
}
}

#endif // LIST_H
