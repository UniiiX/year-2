#ifndef BINARYSEARCHTREEEXCEPTIONS_H
#define BINARYSEARCHTREEEXCEPTIONS_H

#include <stdexcept>
#include <string>

namespace bst
{
    class AbsentKey : public std::invalid_argument
    {
    public:
        explicit AbsentKey(const std::string & what) : std::invalid_argument(what) {}
        explicit AbsentKey(const char* what) : std::invalid_argument(what) {}
        virtual ~AbsentKey() {}
    };

    class InvalidNode : public std::invalid_argument
    {
    public:
        explicit InvalidNode(const std::string & what) : std::invalid_argument(what) {}
        explicit InvalidNode(const char* what) : std::invalid_argument(what) {}
        virtual ~InvalidNode() {}
    };
}

#endif // BINARYSEARCHTREEEXCEPTIONS_H
