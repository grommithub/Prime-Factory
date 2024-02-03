// PrimeFactory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

#include <thread>
#include <mutex>
#include "PrimeFactory.h"
#include <execution>

#include <functional>
#include <string>


#include "ThreadedPrimeFinder.h"



std::chrono::duration<double> benchmark(std::function<void(void)> func)
{
	auto start_time = std::chrono::high_resolution_clock::now();
	func();
	auto end_time = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);
}


std::vector<int> find_primes_single_thread(const int up_to)
{
	std::vector<int> primes = { 2, 3 };

	for (int i = 6; i < up_to; i += 6)
	{
		for (int j = -1; j <= 1; j += 2)
		{
			if (ThreadedPrimeFinder::no_common_factors(i + j, primes))
			{
				primes.push_back(i + j);
			}
		}
	}

	return primes;
}

std::string readable_time(double time)
{
	return std::to_string((int)time / 60) + ':' + std::to_string(fmod(time, 60.0));
}


constexpr int UP_TO = 100'000'000;

int main()
{


	{
		std::vector<int> primes;

		std::cout << "\nSingle core:" << readable_time(benchmark(
			[&primes]()
			{
				primes = find_primes_single_thread(UP_TO);
			}
		).count()) << '\n';
		std::cout << "Primes found:" << primes.size() << "\n\n";
	}

	{
		std::vector<int> primes;

		std::cout << "Threaded: " << readable_time(benchmark(
			[&primes]()
			{
				primes = ThreadedPrimeFinder::find_all_primes(UP_TO);
			}
		).count()) << '\n';
		std::cout << "Primes found:" << primes.size() << '\n';
	}
}

