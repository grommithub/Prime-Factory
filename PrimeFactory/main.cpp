// PrimeFactory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <chrono>

#include <functional>
#include <string>

#include "PrimeFactory.h"

constexpr int UP_TO = 1'000'000'000;

std::chrono::duration<double> benchmark(std::function<void(void)> func)
{
	auto start_time = std::chrono::high_resolution_clock::now();
	func();
	auto end_time = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);
}

inline std::string readable_time(double time)
{
	auto seconds_leading_zero = time - ((int)time / 60) < 10 ? "0" : "";
	return std::to_string((int)time / 60) + ':' + seconds_leading_zero + std::to_string(fmod(time, 60.0));
}

inline void benchmark_single_thread()
{
	std::vector<int> primes;

	std::cout << "Single thread: " << readable_time(benchmark(
		[&primes]()
		{
			primes = PrimeFinder::find_primes_single_thread(UP_TO);
		}
	).count()) << '\n';
	std::cout << "Primes found: " << primes.size() << "\n\n";
}

inline void benchmark_multi_thread()
{
	std::vector<int> primes;

	std::cout << "Threaded: " << readable_time(benchmark(
		[&primes]()
		{
			primes = PrimeFinder::find_primes_threaded(UP_TO);
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