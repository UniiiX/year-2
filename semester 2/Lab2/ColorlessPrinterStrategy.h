#ifndef COLORLESSPRINTERSTRATEGY_H
#define COLORLESSPRINTERSTRATEGY_H

#include <iostream>
#include <PrinterStrategy.h>

namespace bst
{
    template <typename K, typename V>
    class ColorlessPrinterStrategy : public PrinterStrategy<K, V>
    {
    public:
        ColorlessPrinterStrategy() {}
        virtual ~ColorlessPrinterStrategy() {}

        virtual void print(const Node<K, V>* target) const override
        {
            print(target, "");
        }


    protected:
        virtual void printSpecialInfo(const Node<K, V>* target) const {}


    private:
        void print(const Node<K, V>* target, const std::string & indent) const
        {
            if (!target)
                return;
            print(dynamic_cast<Node<K, V>* >(target->getRight()), indent + '\t');
            std::cout << indent << target->getKey();
            printSpecialInfo(target);
            std::cout << std::endl;
            print(dynamic_cast<Node<K, V>* >(target->getLeft()), indent + '\t');
        }
    };
}

#endif // COLORLESSPRINTERSTRATEGY_H
