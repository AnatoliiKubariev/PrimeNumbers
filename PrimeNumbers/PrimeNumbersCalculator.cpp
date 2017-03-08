#include "PrimeNumbersCalculator.h"

#include <thread>

std::vector<size_t> GetPartsSize(const size_t size, const size_t parts_number);

PrimeNumbersCalculator::PrimeNumbersCalculator()
    : numbers(2, false)
    , n_square_primes(0)
{
}

std::vector<int> PrimeNumbersCalculator::GetPrimes(Interval interval)
{
    if(interval.low > interval.high ||
       interval.low < 0 || interval.high < 0)
    {
        return{};
    }

    if(interval.low == 0 || interval.low == 1)
    {
        interval.low = 2;
    }

    NSquarePrimesInitialise(interval);
    if(n_square_primes.size() >= (interval.high - interval.low + 1))
    {
        return FindPrimes(interval);
    }

    auto parts_size = GetPartsSize(interval.high - interval.low + 1, std::thread::hardware_concurrency());
    std::vector<std::thread> threads;
    auto start = interval.low;
    for(auto size : parts_size)
    {
        threads.push_back(std::thread(&PrimeNumbersCalculator::ModifiedEratosthenesSieve, this, start, size));
        start += size;
    }
    for(auto& thread : threads)
    {
        thread.join();
    }

    return FindPrimes(interval);
}
 
void PrimeNumbersCalculator::ModifiedEratosthenesSieve(const size_t start, size_t size)
{
    size += start;
    for(auto i = start; i < size; ++i)
    {
        numbers[i] = true;
    }

    for(auto i = 0; i < n_square_primes.size(); ++i)
    {
        for(auto j = start; j < size; ++j)
        {
            if(j % n_square_primes[i] == 0)
            {
                for(auto k = n_square_primes[i] * n_square_primes[i]; k < size; k += n_square_primes[i])
                {
                    numbers[k] = false;
                }
                break;
            }
        }
    }
}

std::vector<int> PrimeNumbersCalculator::FindPrimes(const Interval& intervals)
{
    std::vector<int> primes;
    for(auto i = intervals.low; i <= intervals.high; ++i)
    {
        if(numbers[i])
        {
            primes.push_back(i);
        }
    }
    return primes;
}

void PrimeNumbersCalculator::NSquarePrimesInitialise(const Interval& interval)
{
    if(numbers.size() > interval.high + 1 ||
       n_square_primes.size() > floor(sqrt(interval.high + 1)) + 1)
    {
        return;
    }

    numbers.resize(interval.high + 1);
    const auto n_square = floor(sqrt(interval.high + 1)) + 1;
    for(auto i = 2; i <= n_square; ++i)
    {
        numbers[i] = true;
    }

    //EratosthenesSieve
    for(auto i = 2; i * i <= n_square; ++i)
    {
        if(numbers[i])
        {
            for(auto j = i * i; j < n_square; j += i)
            {
                numbers[j] = false;
            }
        }
    }

    for(auto i = 0; i <= n_square; ++i)
    {
        if(numbers[i])
        {
            n_square_primes.push_back(i);
        }
    }
}

std::vector<size_t> GetPartsSize(const size_t size, const size_t parts_number)
{
    auto part_size = size / parts_number;
    auto remainder = size % parts_number;
    std::vector<size_t> parts_size(parts_number, part_size);

    auto j = 0;
    for(auto i = 0; i < remainder; ++i)
    {
        ++parts_size[j];
        ++j;
        if(j >= parts_size.size())
        {
            j = 0;
        }
    }
    return parts_size;
}