#pragma once

#include <vector>

namespace PrimeFinder
{
	std::vector<int> find_primes_single_thread(int up_to);
	bool no_common_factors(int num, const std::vector<int>& known_primes);
	
	std::vector<int> find_primes_threaded(int up_to);
	std::vector<int> find_primes_offset_by_thread(int start, int end, int thread_count, int thread_index, const std::vector<int>& known_primes);
};


