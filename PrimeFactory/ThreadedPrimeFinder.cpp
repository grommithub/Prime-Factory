#include "ThreadedPrimeFinder.h"

#include <algorithm>
#include <thread>
#include <future>
#include <iostream>
#include <string>

using namespace ThreadedPrimeFinder;


std::vector<int> ThreadedPrimeFinder::find_primes_in_range(int start, int end, const std::vector<int>& known_primes)
{
	std::vector<int> primes;

	for (int i = start; i < end; i++)
	{
		if (i % 6 != 1 && i % 6 != 5) continue;


		if (no_common_factors(i, known_primes))
		{
			primes.push_back(i);
		}
	}

	return primes;
}

std::vector<int> ThreadedPrimeFinder::find_all_primes(const int up_to)
{

	std::vector<int> primes;

	if (up_to >= 2) primes.push_back(2);
	if (up_to >= 3) primes.push_back(3);


	int smallest_unchecked_number = primes.back() + 2;

	auto num_of_threads = std::thread::hardware_concurrency();


	std::vector<std::thread> threads(num_of_threads);

	std::cout << "Using " << num_of_threads << " threads\n";

	while (smallest_unchecked_number < up_to)
	{
		int biggest_prime_squared = 0;
		if (primes.back() < sqrt(INT32_MAX))
		{
			biggest_prime_squared = std::min(primes.back() * primes.back(), up_to);
		}
		else
		{
			biggest_prime_squared = up_to;
		}



		std::vector<std::promise<std::vector<int>>> prime_chunks_promises(num_of_threads);
		std::vector<std::future<std::vector<int>>> prime_chunks(num_of_threads);

		int chunk_size = (biggest_prime_squared - smallest_unchecked_number) / num_of_threads;

		for (int i = 0; i < num_of_threads; i++)
		{
			std::future<std::vector<int>> primes_future = prime_chunks_promises[i].get_future();
			prime_chunks[i] = std::move(primes_future);

			int start = smallest_unchecked_number + (i * chunk_size);
			int end = start + chunk_size;
			if (i == num_of_threads - 1)
			{
				end = biggest_prime_squared;
				smallest_unchecked_number = end + 1;
			}

#if _DEBUG
			std::cout << "Making thread for: " << start << " -> " << end << std::endl;
#endif

			auto thread = std::thread([i, &prime_chunks_promises, primes, smallest_unchecked_number, start, end]()
				{
					std::vector<int> result = find_primes_in_range(start, end, primes);
					prime_chunks_promises[i].set_value(result);
				});
			threads[i] = (std::move(thread));
		}

		for (auto& thread : threads)
		{
			if (thread.joinable())
			{
				thread.join();
			}
		}

		for (auto& prime_chunk : prime_chunks)
		{
			auto chunk = prime_chunk.get();
			primes.insert(primes.end(), chunk.begin(), chunk.end());

		}


	}
	return primes;

}

bool ThreadedPrimeFinder::no_common_factors(int num, const std::vector<int>& primes)
{
	return std::none_of(primes.begin(), std::find_if(primes.begin(), primes.end(), [num](auto a) { return a * a > num; }), [num](unsigned int a) { return num % a == 0; });
}

