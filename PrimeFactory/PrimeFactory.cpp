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


constexpr int UP_TO = 1'000'000'000;

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
		std::cout << "Primes found:" << primes.size() << '\n';
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



	//std::vector<int> primes;
	//primes.push_back(2);
	//primes.push_back(3);

	//primes.reserve(100'000);

	//auto start_time = std::chrono::high_resolution_clock::now();

	//for (int i = 6; i < 1'000'000; i += 6)
	//{
	//	for (int j = -1; j <= 1; j += 2)
	//	{
	//		if (no_common_factors(i + j, primes))
	//		{
	//			primes.push_back(i + j);
	//			//if (primes.size() % 1'000'000 == 0)
	//			//{
	//			//	std::cout << primes.size() << " Biggest prime so far: " << primes.back() << '\n';
	//			//}
	//		}
	//	}
	//}
	//auto end_time = std::chrono::high_resolution_clock::now();

	//std::cout << "Par time : " << benchmark([primes]() { std::for_each(std::execution::par, primes.begin(), primes.end(), [](const auto p) { std::cout << std::to_string(p) + '\n'; }); });




	//std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);

	//std::cout << "Done! " << primes.size() << '\n';
	//std::cout << "Exection time : " << duration.count() << " seconds\n";




	//std::vector<std::thread> threads;
	//auto thread_count = std::thread::hardware_concurrency();

	//std::vector<int> primesB;
	//primes.push_back(2);
	//primes.push_back(3);


	//int current = 3; int high = 9;
	//while (current < 1'000'000)
	//{
	//	int chunkSize = (high - current) / thread_count;
	//	
	//	for (int i = 0; i < thread_count; i++)
	//	{
	//		auto start = current + 
	//	}
	//	
	//	threads.emplace_back()


	//}


	//for (auto& thread : threads)
	//{
	//	thread.join();
	//}




}

