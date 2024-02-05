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




std::string readable_time(double time)
{
	return std::to_string((int)time / 60) + ':' + std::to_string(fmod(time, 60.0));
}


constexpr int UP_TO = 100'000'000;

int main()
{


	//{
	//	std::vector<int> primes;

	//	std::cout << "\nSingle core:" << readable_time(benchmark(
	//		[&primes]()
	//		{
	//			primes = ThreadedPrimeFinder::find_primes_single_thread(UP_TO);
	//		}
	//	).count()) << '\n';
	//	std::cout << "Primes found:" << primes.size() << "\n\n";
	//}

	{
		std::vector<int> primes;

		std::cout << "Threaded: " << readable_time(benchmark(
			[&primes]()
			{
				primes = ThreadedPrimeFinder::find_all_primes(UP_TO);
			}
		).count()) << '\n';

		//auto check = ThreadedPrimeFinder::find_primes_single_thread(UP_TO);

	/*	std::vector<int> diff;*/

		//std::set_difference(primes.begin(), primes.end(), check.begin(), check.end(), std::inserter(diff, diff.begin()));

		//std::sort(diff.begin(), diff.end());
		
		std::cout << "Primes found:" << primes.size() << '\n';	
		
	}

}

