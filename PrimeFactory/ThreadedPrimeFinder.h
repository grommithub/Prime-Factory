#pragma once
#include <vector>



namespace PrimeFinder
{
	std::vector<int> find_primes_single_thread(const int up_to);
	bool no_common_factors(int num, const std::vector<int>& primes);
	
	
	std::vector<int> find_primes_in_range(int start, int end, const std::vector<int>& knownPrimes);
	std::vector<int> find_all_primes(int up_to);
	std::vector<int> calculate_primes_horizontally(int start, int end, int thread_count, int thread_index, const std::vector<int>& known_primes);
};


