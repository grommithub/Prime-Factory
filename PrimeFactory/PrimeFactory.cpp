#include "PrimeFactory.h"

#include <algorithm>
#include <thread>
#include <future>

#include <iostream>

using namespace PrimeFinder;


std::vector<int> PrimeFinder::find_primes_single_thread(int up_to)
{
	if (up_to < 2) return std::vector<int>();
	if (up_to == 3) return std::vector<int> { 2 };

	std::vector<int> primes = { 2, 3 };

	for (int i = 6; i < up_to; i += 6)
	{
		for (int j = -1; j <= 1; j += 2)
		{
			if (no_common_factors(i + j, primes))
			{
				primes.push_back(i + j);
			}
		}
	}

	return primes;
}

std::vector<int> PrimeFinder::find_primes_offset_by_thread(int start, int end, int thread_count, int thread_index, const std::vector<int>& known_primes)
{
	start += 6 - (start % 6) + 6 * thread_index;

	std::vector<int> primes;
	for (int i = start; i < end; i += 6 * thread_count)
	{
		for (int j = -1; j <= 1; j += 2)
		{
			if (no_common_factors(i + j, known_primes))
			{
				primes.push_back(i + j);
			}
		}
	}

	return primes;
}



std::vector<int> PrimeFinder::find_primes_threaded(int up_to)
{
	//Using a single thread seems to be faster up to ~1.5 million on my machine
	constexpr int single_core_up_to = 1'000'000;
	std::vector<int> primes = find_primes_single_thread(std::min(up_to, single_core_up_to));

	auto num_of_threads = std::thread::hardware_concurrency();
	std::vector<std::thread> threads(num_of_threads);

	std::cout << "Using " << num_of_threads << " threads\n";

	int smallest_unchecked_number = single_core_up_to + 1;

	while (smallest_unchecked_number < up_to)
	{
		int temp_up_to = up_to;
		if (primes.back() < sqrt(up_to))
		{
			temp_up_to = primes.back() * primes.back();
		}

		std::vector<std::promise<std::vector<int>>> prime_chunks_promises(num_of_threads);
		std::vector<std::future<std::vector<int>>> prime_chunks(num_of_threads);

		for (int thread_index = 0; thread_index < num_of_threads; thread_index++)
		{
			std::future<std::vector<int>> primes_future = prime_chunks_promises[thread_index].get_future();
			prime_chunks[thread_index] = std::move(primes_future);

			int start = smallest_unchecked_number;
			int end = temp_up_to;

			auto thread = std::thread([thread_index, &prime_chunks_promises, primes, smallest_unchecked_number, start, end, num_of_threads]()
				{
					std::vector<int> result = find_primes_offset_by_thread(start, end, num_of_threads, thread_index, primes);
					prime_chunks_promises[thread_index].set_value(result);
				});
			threads[thread_index] = (std::move(thread));
		}

		smallest_unchecked_number = temp_up_to;

		for (auto& thread : threads)
		{
			if (thread.joinable())
			{
				thread.join();
			}
		}

		size_t new_primes_first_index = primes.size();
		for (auto& prime_chunk : prime_chunks)
		{
			auto chunk = prime_chunk.get();
			primes.resize(primes.size() + chunk.size());
			std::merge(primes.begin() + new_primes_first_index, primes.begin() + primes.size() - chunk.size(), chunk.begin(), chunk.end(), primes.begin());
		}
	}
	return primes;

}

bool PrimeFinder::no_common_factors(int num, const std::vector<int>& primes)
{
	auto biggest_prime_to_check = std::find_if(primes.begin(), primes.end(), [num](auto a) { return a * a > num; });
	return std::none_of(primes.begin(), biggest_prime_to_check, [num](unsigned int a) { return num % a == 0; });
}
