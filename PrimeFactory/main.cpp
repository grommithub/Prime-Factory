// PrimeFactory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <chrono>

#include <functional>
#include <string>

#include "PrimeFactory.h"

constexpr int UP_TO = 100'000'000;

std::chrono::duration<double> benchmark(std::function<void(void)> func)
{
	auto start_time = std::chrono::high_resolution_clock::now();
	func();
	auto end_time = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);
}

std::string readable_time(double time)
{
	return std::to_string((int)time / 60) + ':' + std::to_string(fmod(time, 60.0));
}

void benchmark_multi_thread()
{
	std::vector<int> primes;

	std::cout << "Threaded: " << readable_time(benchmark(
		[&primes]()
		{
			primes = PrimeFinder::find_all_primes(UP_TO);
		}
	).count()) << '\n';


	std::cout << "Primes found: " << primes.size() << "\n\n";
}

void benchmark_single_thread()
{
	std::vector<int> primes;

	std::cout << "Single core: " << readable_time(benchmark(
		[&primes]()
		{
			primes = PrimeFinder::find_primes_single_thread(UP_TO);
		}
	).count()) << '\n';
	std::cout << "Primes found: " << primes.size() << "\n\n";
}

int main()
{

#if _DEBUG
	std::cout << "[Running in debug mode. Compiling to release will significantly boost performance]\n\n";
#endif

	std::cout << "Finding primes up to " << UP_TO << "\n\n";

	benchmark_single_thread();
	
	benchmark_multi_thread();


	system("pause");

	return 0;
}