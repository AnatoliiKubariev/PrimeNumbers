#include "PrimeNumbersCalculator.h"
#include "XMLHandler.h"

#include <fstream>
#include <string>

int main(int argc, char **argv)
{
    if(argc < 1)
    {
        return 1;
    }

    std::string file_name;
    for(int i = 1; i < argc; i++)
    {
        file_name += argv[i];
    }

    PrimeNumbersCalculator calc;
    std::vector<int> primes;
    for(auto& interval : GetIntervals(file_name))
    {
        for(auto prime : calc.GetPrimes(interval))
        {
            primes.push_back(prime);
        }
    }

    WritePrimes(file_name, primes);

    return 0;
}