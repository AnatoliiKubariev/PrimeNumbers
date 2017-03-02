#pragma once

#include "Interval.h"

#include <vector>
#include <iostream>

std::vector<Interval> GetItervals(std::istream& stream);

void WritePrimals(std::ostream& stream, const std::vector<int>& primals);
