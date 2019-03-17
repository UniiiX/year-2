#ifndef PRIMENUMBERSGENERATOR_H
#define PRIMENUMBERSGENERATOR_H


class PrimeNumbersGenerator
{
    public:
        PrimeNumbersGenerator();
        virtual ~PrimeNumbersGenerator();
        static unsigned minPrimeNumberGreaterThan(unsigned number);

    private:
        static bool isPrime(unsigned number);
};

#endif // PRIMENUMBERSGENERATOR_H
