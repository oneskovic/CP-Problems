#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <numeric>
using namespace std;
#define ll long long

struct factor
{
	ll value;
	int count;
};
bool operator>(const factor& lhs, const factor& rhs)
{
	return lhs.count > rhs.count;
}

vector<factor> factorize(ll number)
{
	vector<factor> factors;
	ll candidate_factor = 2;
	while (candidate_factor * candidate_factor <= number)
	{
		factor new_factor = { candidate_factor,0 };
		while (number % candidate_factor == 0)
		{
			number /= candidate_factor;
			new_factor.count++;
		}
		if (new_factor.count > 0)
			factors.push_back(new_factor);
		candidate_factor++;
	}
	if (number > 1)
		factors.push_back({ number,1 });
	return factors;
}

int main()
{
	ios::sync_with_stdio(false);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		ll number; cin >> number;
		auto factors = factorize(number);
		sort(factors.begin(), factors.end(),greater<factor>());

		ll current_product = 1;
		vector<ll> solution;
		for (size_t i = 0; i < factors.size()-1; i++)
		{
			int next_factor_count = factors[i + 1].count;
			current_product *= factors[i].value;
			while (factors[i].count > next_factor_count)
			{
				solution.push_back(current_product);
				factors[i].count--;
			}
		}
		current_product *= factors.back().value;
		for (size_t i = 0; i < factors.back().count; i++)
			solution.push_back(current_product);
		
		cout << solution.size() << "\n";
		for (ll element: solution)
			cout << element << " ";
		cout << "\n";
	}
	return 0;
}