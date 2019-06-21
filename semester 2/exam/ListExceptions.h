#ifndef LISTEXCEPTIONS_H
#define LISTEXCEPTIONS_H

#include <exception>
#include <string>

class InvalidIndex : public std::out_of_range
{
    public:
        InvalidIndex(const std::string & what) :
            std::out_of_range(what)
        {

        }

        InvalidIndex(const char* what) :
            std::out_of_range(what)
        {

        }

        virtual ~InvalidIndex() {}
};

#endif // LISTEXCEPTIONS_H
