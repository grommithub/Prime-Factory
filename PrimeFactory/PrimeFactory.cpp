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


inline bool no_common_factors(int num, std::vector<int>& primes)
{
	return std::none_of(primes.begin(), std::find_if(primes.begin(), primes.end(), [num](auto a) { return a * a > num; }), [num](unsigned int a) { return num % a == 0; });
}


std::chrono::duration<double> benchmark(std::function<void(void)> func)
{
	auto start_time = std::chrono::high_resolution_clock::now();
	func();
	auto end_time = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);
}


int main()
{

	std::vector<int> primes;
	primes.push_back(2);
	primes.push_back(3);

	primes.reserve(100'000);

	auto start_time = std::chrono::high_resolution_clock::now();

	for (int i = 6; i < 1'000'000; i += 6)
	{
		for (int j = -1; j <= 1; j += 2)
		{
			if (no_common_factors(i + j, primes))
			{
				primes.push_back(i + j);
				//if (primes.size() % 1'000'000 == 0)
				//{
				//	std::cout << primes.size() << " Biggest prime so far: " << primes.back() << '\n';
				//}
			}
		}
	}
	auto end_time = std::chrono::high_resolution_clock::now();

	std::cout << "Par time : " << benchmark([primes]() { std::for_each(std::execution::par, primes.begin(), primes.end(), [](const auto p) { std::cout << std::to_string(p) + '\n'; }); });




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



//void add_primes_in_range(std::vector<int>& primes, int start, int end)
//{
//	for (int i = start; i < end; i += 6)
//	{
//		for (int j = -1; j <= 1; j += 2)
//		{
//			if (no_common_factors(i + j, primes))
//			{
//				primes.push_back(i + j);
//				if (primes.size() % 1'000'000 == 0)
//				{
//					std::cout << primes.size() << " Biggest prime so far: " << primes.back() << '\n';
//				}
//			}
//		}
//	}
//}

