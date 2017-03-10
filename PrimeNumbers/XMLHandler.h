#pragma once

#include "Interval.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<Interval> GetIntervals(const std::string& file_name);
std::vector<Interval> GetIntervals(std::istream& stream);

void WritePrimes(const std::string& file_name, const std::vector<int>& primes);
void WritePrimes(std::fstream& stream, const std::vector<int>& primes);
