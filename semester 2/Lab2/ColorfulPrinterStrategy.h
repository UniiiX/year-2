#ifndef COLORFULPRINTERSTRATEGY_H
#define COLORFULPRINTERSTRATEGY_H

#include <ColorlessPrinterStrategy.h>

namespace bst
{
    template <typename K, typename V>
    class ColorfulPrinterStrategy : public ColorlessPrinterStrategy<K, V>
    {
    public:
        ColorfulPrinterStrategy() {}
        virtual ~ColorfulPrinterStrategy() {}

    protected:
        void printSpecialInfo(const Node<K, V>* target) const override
        {
            std::string color = (target->getColor() == Color::black) ? "{B}" : "{R}";
            std::cout << color;
        }
    };
}

#endif // COLORFULPRINTERSTRATEGY_H
