// PrimeFactory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

#include <thread>
#include <mutex>




inline bool no_common_factors(int num, std::vector<int>& primes)
{
	return std::none_of(primes.begin(), std::find_if(primes.begin(), primes.end(), [num](auto a) { return a * a > num; }), [num](unsigned int a) { return num % a == 0; });
}

int main()
{
	auto start_time = std::chrono::high_resolution_clock::now();

	std::vector<std::thread> threads;

	std::vector<int> primes;
	primes.push_back(2);
	primes.push_back(3);

	for (int i = 6; i < 1'000'000'000; i += 6)
	{
		for (int j = -1; j <= 1; j += 2)
		{
			if(no_common_factors(i + j, primes))
			{
				primes.push_back(i + j);
				if (primes.size() % 1'000'000 == 0)
				{
					std::cout << primes.size() << " Biggest prime so far: " << primes.back() << '\n';
				}
			}
		}
	}

	auto end_time = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);
	std::cout << "Exection time : " << duration.count() << " seconds\n";

	std::cout << "Done! " << primes.size() << '\n';

#if 0
	for (auto prime : primes)
	{
		std::cout << prime << '\n';
	}
#endif // 0

}

