#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;
#define ll long long

vector<ll> prime_factors(ll n)
{
	vector<ll> factors;
	ll i = 2;
	while (i*i <= n)
	{
		if (n%i == 0)
		{
			factors.push_back(i);
		}
		while (n % i == 0)
			n /= i;
		i++;
	}
	if (n > 1)
		factors.push_back(n);
	return factors;
}

vector<ll> all_divisors(ll n)
{
	vector<ll> divisors;
	ll i = 2;
	while (i*i <= n)
	{
		if (n%i == 0)
		{
			divisors.push_back(i);
			if (i*i != n)
				divisors.push_back(n / i);
		}
		i++;
	}
	divisors.push_back(n);
	return divisors;
}


void print_solution(const vector<ll>& permutation, map<ll, set<ll>>& divisors_divisible_by)
{
	vector<ll> number_in_intersection;
	for (size_t i = 0; i < permutation.size(); i++)
	{
		auto& divisible_by_current = divisors_divisible_by.at(permutation[i]);
		auto& divisible_by_next = divisors_divisible_by.at(permutation[(i + 1) % permutation.size()]);
		auto intersection = vector<ll>();
		for (ll divisor : divisible_by_current)
		{
			if (divisible_by_next.find(divisor) != divisible_by_next.end())
			{
				intersection.push_back(divisor);
				break;
			}
		}

		if (intersection.empty())
		{
			number_in_intersection.push_back(-1);
		}
		else
		{
			number_in_intersection.push_back(intersection.back());
			divisors_divisible_by[permutation[i]].erase(intersection.back());
			divisors_divisible_by[permutation[(i + 1) % permutation.size()]].erase(intersection.back());
		}
	}

	set<ll> taken;
	for (size_t i = 0; i < permutation.size(); i++)
	{
		auto divisible_by_current = divisors_divisible_by.at(permutation[i]);
		for (ll number : divisible_by_current)
		{
			if (taken.find(number) == taken.end())
			{
				cout << number << " ";
				taken.insert(number);
			}
		}
		if (number_in_intersection[i] != -1)
		{
			cout << number_in_intersection[i] << " ";
			taken.insert(number_in_intersection[i]);
		}
	}
	cout << "\n";
	

	for (size_t i = 0; i < permutation.size(); i++)
	{
		if (number_in_intersection[i] > -1)
		{
			divisors_divisible_by[permutation[i]].insert(number_in_intersection[i]);
			divisors_divisible_by[permutation[(i + 1) % permutation.size()]].insert(number_in_intersection[i]);
		}
	}
}


ll evaluate_permutation(const vector<ll>& permutation, map<ll, set<ll>>& divisors_divisible_by, bool print_solution = false)
{
	if (print_solution)
	{
		ios::sync_with_stdio(false);
		cin.tie(0);
	}
	ll to_add = 0;
	vector<ll> number_in_intersection;
	for (size_t i = 0; i < permutation.size(); i++)
	{
		auto& divisible_by_current = divisors_divisible_by.at(permutation[i]);
		auto& divisible_by_next = divisors_divisible_by.at(permutation[(i+1)%permutation.size()]);
		auto intersection = vector<ll>();
		for (ll divisor: divisible_by_current)
		{
			if (divisible_by_next.find(divisor) != divisible_by_next.end())
			{
				intersection.push_back(divisor);
				break;
			}
		}

		if (intersection.empty())
		{
			to_add++;
			number_in_intersection.push_back(-1);
		}
		else
		{
			number_in_intersection.push_back(intersection.back());
			divisors_divisible_by[permutation[i]].erase(intersection.back());
			divisors_divisible_by[permutation[(i + 1) % permutation.size()]].erase(intersection.back());
		}
	}

	set<ll> taken;
	if (print_solution)
	{
		for (size_t i = 0; i < permutation.size(); i++)
		{
			auto divisible_by_current = divisors_divisible_by.at(permutation[i]);
			for (ll number : divisible_by_current)
			{
				if (taken.find(number) == taken.end())
				{
					cout << number << " ";
					taken.insert(number);
				}
			}
			if (number_in_intersection[i] != -1)
			{
				cout << number_in_intersection[i] << " ";
				taken.insert(number_in_intersection[i]);
			}
		}
		cout << "\n";
	}

	for (size_t i = 0; i < permutation.size(); i++)
	{
		if (number_in_intersection[i] > -1)
		{
			divisors_divisible_by[permutation[i]].insert(number_in_intersection[i]);
			divisors_divisible_by[permutation[(i + 1) % permutation.size()]].insert(number_in_intersection[i]);
		}
	}

	return to_add;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_count; cin >> test_count;
	for (size_t test_no	= 0; test_no < test_count; test_no++)
	{
		ll n; cin >> n;
		auto factors = prime_factors(n);
		auto divisors = all_divisors(n);
		sort(divisors.begin(), divisors.end());

		map<ll, set<ll>> divisors_divisible_by;
		for (size_t i = 0; i < divisors.size(); i++)
		{
			ll current_divisor = divisors[i];
			for (ll factor: factors)
				if (current_divisor % factor == 0)
					divisors_divisible_by[factor].insert(current_divisor);
		}

		ll best_solution = LLONG_MAX;
		vector<ll> best_permutation;
		do
		{
			ll new_solution = evaluate_permutation(factors, divisors_divisible_by);
			if (new_solution < best_solution)
			{
				best_solution = new_solution;
				best_permutation = factors;
			}
		} while (next_permutation(factors.begin(), factors.end()));
		
		evaluate_permutation(best_permutation, divisors_divisible_by);
		cout << best_solution << "\n";
	}
	return 0;
}