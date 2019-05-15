#ifndef PRINTERPROXY_H
#define PRINTERPROXY_H

#include <Printer.h>
#include <ColorfulPrinterStrategy.h>
#include <SplayTreeImpl.h>

namespace bst
{
    template <typename K, typename V>
    class PrinterProxy
    {
    public:
        PrinterProxy() = delete;
        PrinterProxy(const PrinterProxy &) = delete;
        PrinterProxy(PrinterProxy &&) = delete;
        virtual ~PrinterProxy() = delete;
        PrinterProxy & operator=(const PrinterProxy &) = delete;
        PrinterProxy & operator=(PrinterProxy &&) = delete;

        static void print(const BinarySearchTree<K, V> & target)
        {
            TreeType type = target.getType();
            switch (type)
            {
                case (TreeType::binarySearchTree):
                {
                    Printer<K, V>(new ColorlessPrinterStrategy<K, V>).print(target);
                    break;
                }
                case (TreeType::splayTree):
                {
                    Printer<K, V>(new ColorlessPrinterStrategy<K, V>).print(target);
                    break;
                }
                case (TreeType::redBlackTree):
                {
                    Printer<K, V>(new ColorfulPrinterStrategy<K, V>).print(target);
                    break;
                }
            }
        }
    };

}

#endif // PRINTERPROXY_H
