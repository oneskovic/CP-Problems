#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll unsigned long long

void construct_divisors(const vector<ll>& prime_divisors, int position, ll number, ll current_divisor, vector<ll>& output_divisors)
{
	if (position == prime_divisors.size())
	{
		if (number % current_divisor == 0)
		{
			output_divisors.push_back(current_divisor);
		}
		return;
	}
	ll prime_divisor = prime_divisors[position];
	ll divisor = current_divisor;
	do
	{
		construct_divisors(prime_divisors, position + 1, number, divisor, output_divisors);
		divisor *= prime_divisor;
	} while (number % divisor == 0);
}

vector<ll> all_divisors(ll number)
{
	ll divisor_candidate = 2;
	ll number_copy = number;
	vector<ll> prime_divisors;
	while (divisor_candidate * divisor_candidate <= number)
	{
		if (number % divisor_candidate == 0)
			prime_divisors.push_back(divisor_candidate);
		
		while (number % divisor_candidate == 0)
			number /= divisor_candidate;

		divisor_candidate++;
	}
	if (number > 1)
		prime_divisors.push_back(number);
	
	vector<ll> divisors;
	construct_divisors(prime_divisors, 0, number_copy, 1, divisors);
	return divisors;
}

int main()
{
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		ll p, q; cin >> p >> q;
		ll q_start = q;
		ll max_x = 1;
		auto divisors_of_q = all_divisors(q);
		for (ll divisor: divisors_of_q)
		{
			if (divisor <= p)
			{
				ll x = p;
				while (x % divisor == 0)
				{
					x /= divisor;
					if (p % x == 0 && x % q > 0)
						max_x = max(max_x, x);
					
					if (divisor == 1)
						break;
				}
			}
		}
		cout << max_x << "\n";
	}

	return 0;
}