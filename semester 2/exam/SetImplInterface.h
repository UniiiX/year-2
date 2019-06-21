#ifndef SETIMPLINTERFACE_H
#define SETIMPLINTERFACE_H

namespace advalg
{
template <typename K>
class SetImplInterface
{
public:
    SetImplInterface() {}
    virtual ~SetImplInterface() {}

    virtual bool belongs(const K & key) = 0;
    virtual void insert(const K & key) = 0;
    virtual void remove(const K & key) = 0;
};
}

#endif // SETIMPLINTERFACE_H
