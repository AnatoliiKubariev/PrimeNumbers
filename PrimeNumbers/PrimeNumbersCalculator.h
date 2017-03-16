#pragma once

#include "Interval.h"

#include <atomic>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class PrimeNumbersCalculator
{
public:
    ~PrimeNumbersCalculator();
    PrimeNumbersCalculator();

    std::vector<int> GetPrimes(Interval intervals);

private:
    void ModifiedEratosthenesSieve(const size_t thread_id);
    std::vector<int> FindPrimes(const Interval& intervals);
    void NSquarePrimesInitialise(const Interval& intervals);

    std::deque<bool> numbers;
    std::vector<int> n_square_primes;

    std::queue<Interval> processing_parts;
    std::vector<std::thread> threads;
    std::mutex mutex_sieve;
    std::condition_variable condition_work;
    std::condition_variable condition_finished;
    std::atomic_uint8_t tasks_counter;
    bool finished;
};