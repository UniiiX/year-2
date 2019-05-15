#ifndef PRINTERSTRATEGY_H
#define PRINTERSTRATEGY_H


namespace bst
{
    template <typename K, typename V>
    class PrinterStrategy
    {
        public:
            PrinterStrategy() {}
            virtual ~PrinterStrategy() {}

            virtual void print(const Node<K, V>* target) const = 0;
    };
}

#endif // PRINTERSTRATEGY_H
