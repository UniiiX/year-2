#include "PrimeNumbersGenerator.h"

#include <cmath>

PrimeNumbersGenerator::PrimeNumbersGenerator()
{

}

PrimeNumbersGenerator::~PrimeNumbersGenerator()
{

}

bool PrimeNumbersGenerator::isPrime(unsigned number)
{
    for (int divider(2); divider < sqrt(number); divider++)
    {
        if (number % divider == 0)
        {
            return false;
        }
    }
    return true;
}

unsigned PrimeNumbersGenerator::minPrimeNumberGreaterThan(unsigned number)
{
    for (int i(number); ; i++)
    {
        if (isPrime(i))
        {
            return i;
        }
    }
}
