#pragma once

#include "Interval.h"

#include <vector>
#include <iostream>
#include <fstream>

std::vector<Interval> GetIntervals(std::istream& stream);

void WritePrimes(std::fstream& stream, const std::vector<int>& primals);
