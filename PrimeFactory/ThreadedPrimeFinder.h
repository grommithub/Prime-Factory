#pragma once
#include <vector>



namespace ThreadedPrimeFinder
{
	std::vector<int> find_primes_single_thread(const int up_to);


	std::vector<int> find_primes_in_range(int start, int end, const std::vector<int>& knownPrimes);
	std::vector<int> find_all_primes(const int up_to);
};

bool no_common_factors(int num, const std::vector<int>& primes);

