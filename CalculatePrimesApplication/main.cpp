#include "PrimeNumbersCalculator.h"
#include "XMLHandler.h"

#include <fstream>
#include <string>
#include <iostream>

int main(int argc, char **argv)
{
    if(argc <= 1)
    {
        std::cerr << "No file name" << std::endl;
        return 1;
    }

    std::string file_name;
    for(int i = 1; i < argc; i++)
    {
        file_name += argv[i];
    }

    PrimeNumbersCalculator calc;
    std::vector<int> primes;
    try
    {
    for(auto& interval : GetIntervals(file_name))
    {
        for(auto prime : calc.GetPrimes(interval))
        {
            primes.push_back(prime);
        }
    }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exeption: " << e.what() << std::endl;
        return 1;
    }

    WritePrimes(file_name, primes);

    std::cout << "Task complete" << std::endl;
    return 0;
}