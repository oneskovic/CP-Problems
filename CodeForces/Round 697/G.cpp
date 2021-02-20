#include <algorithm>
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;
#define ll long long

vector<vector<ll>> divisors_sieve(ll max_n)
{
	vector<vector<ll>> divisors(max_n + 1, vector<ll>());
	for (size_t i = 1; i <= max_n; i++)
	{
		for (size_t j = 2 * i; j <= max_n; j += i)
			divisors[j].push_back(i);
	}
	return divisors;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		vector<ll> numbers(n);
		ll max_number = 0;
		unordered_map<ll, int> count_number;
		for (size_t i = 0; i < n; i++)
		{
			cin >> numbers[i];
			count_number[numbers[i]]++;
			max_number = max(max_number, numbers[i]);
		}
		auto divisors = divisors_sieve(max_number);
		sort(numbers.begin(), numbers.end());
		numbers.erase(unique(numbers.begin(), numbers.end()), numbers.end());

		unordered_map<ll, ll> dp;
		dp[numbers[0]] = count_number[numbers[0]];
		for (size_t i = 1; i < n; i++)
		{
			ll current_number = numbers[i];
			dp[current_number] = count_number[current_number];
			ll max_divisor_dp = 0;
			for (ll divisor: divisors[current_number])
				max_divisor_dp = max(max_divisor_dp, dp[divisor]);
			dp[current_number] += max_divisor_dp;
		}
		
		ll solution = 0;
		for (auto kvp: dp)
			solution = max(solution, kvp.second);
		cout << n - solution << "\n";
	}
	return 0;
}