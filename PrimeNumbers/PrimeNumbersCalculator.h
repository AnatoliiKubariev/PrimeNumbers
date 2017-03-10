#pragma once

#include "Interval.h"

#include <deque>
#include <vector>

class PrimeNumbersCalculator
{
public:
    PrimeNumbersCalculator();

    std::vector<int> GetPrimes(Interval intervals);

private:
    void ModifiedEratosthenesSieve(const size_t start, size_t size);
    std::vector<int> FindPrimes(const Interval& intervals);
    void NSquarePrimesInitialise(const Interval& intervals);

    std::deque<bool> numbers;
    std::vector<int> n_square_primes;
};