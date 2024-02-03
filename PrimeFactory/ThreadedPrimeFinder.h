#pragma once
#include <vector>

namespace ThreadedPrimeFinder
{
	std::vector<int> find_primes_in_range(int start, int end, const std::vector<int>& knownPrimes);
	std::vector<int> find_all_primes(const int up_to);
	inline bool no_common_factors(int num, const std::vector<int>& primes);
};

