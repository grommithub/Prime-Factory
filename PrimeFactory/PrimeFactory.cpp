// PrimeFactory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

int main()
{

	std::vector<unsigned int> primes;

	auto biggest_possible_prime_it = primes.begin();

	for (unsigned int i = 2; i < 1'000'000'000; i++)
	{
		biggest_possible_prime_it = std::find_if(biggest_possible_prime_it, primes.end(), [i](auto a) { return a > sqrt(i); });
		if (std::none_of(primes.begin(), biggest_possible_prime_it, [i](unsigned int a) { return i % a == 0; }))
		{
			primes.push_back(i);
			if (primes.size() % 100 == 0)
			{
				std::cout << primes.size() << '\n';
			}
		}
	}

	int* a = (int*)malloc(sizeof(int));


	std::cout << "Done! " << primes.size() << '\n';

#if 0
	for (auto prime : primes)
	{
		std::cout << prime << '\n';
	}
#endif // 0

}

