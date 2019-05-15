#ifndef PRINTER_H
#define PRINTER_H

#include <BinarySearchTree.h>
#include <PrinterStrategy.h>

namespace bst
{
    template <typename K, typename V>
    class Printer
    {
    public:
        Printer(PrinterStrategy<K, V>* strategy) :
            strategy(strategy)
        {

        }

        virtual ~Printer()
        {
            delete strategy;
        }

        void print(const BinarySearchTree<K, V> & target) const
        {
            strategy->print(target.getRoot());
        }

    protected:
        PrinterStrategy<K, V>* strategy;
    };
}

#endif // PRINTER_H
