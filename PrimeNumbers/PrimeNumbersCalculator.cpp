#include "PrimeNumbersCalculator.h"

PrimeNumbersCalculator::PrimeNumbersCalculator()
    : numbers(2, 0)
{
}

std::vector<int> PrimeNumbersCalculator::GetPrimals(const Interval& interval)
{
    if(interval.high < numbers.size() + 1)
    {
        return FindPrimals(interval);
    }

    numbers.resize(interval.high + 1);
    for(auto i = 2; i < interval.high + 1; ++i)
    {
        numbers[i] = 1;
    }

    EratosthenesSieve();

    return FindPrimals(interval);
}

void PrimeNumbersCalculator::EratosthenesSieve()
{
    for(auto i = 2; i * i < numbers.size(); ++i)
    {
        if(numbers[i] == 1)
        {
            for(auto j = i * i; j < numbers.size(); j += i)
            {
                numbers[j] = 0;
            }
        }
    }
}

std::vector<int> PrimeNumbersCalculator::FindPrimals(const Interval& intervals)
{
    std::vector<int> primals;
    for(auto i = intervals.low; i < intervals.high; ++i)
    {
        if(numbers[i] == 1)
        {
            primals.push_back(i);
        }
    }
    return primals;
}