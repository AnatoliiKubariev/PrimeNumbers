#pragma once

#include <vector>
#include "Interval.h"

#include <vector>


class PrimeNumbersCalculator
{
public:
    PrimeNumbersCalculator();

    std::vector<int> GetPrimals(const Interval& intervals);

private:
    void EratosthenesSieve();
    std::vector<int> FindPrimals(const Interval& intervals);

    std::vector<int> numbers;
};