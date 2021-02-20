#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
#define ll long long
constexpr ll mod = 1e9 + 7;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, k, query_count; cin >> n >> k >> query_count;
	auto dp = vector<vector<ll>>(n, vector<ll>(k + 1));

	for (int position = 0; position < n; position++)
		dp[position][0] = 1;
	
	for (int number_of_steps = 1; number_of_steps <= k; number_of_steps++)
	{
		for (int position = 0; position < n; position++)
		{
			if (position > 0)
			{
				dp[position][number_of_steps] += dp[position - 1][number_of_steps - 1];
				dp[position][number_of_steps] %= mod;
			}
			if (position < n - 1)
			{
				dp[position][number_of_steps] += dp[position + 1][number_of_steps - 1];
				dp[position][number_of_steps] %= mod;
			}
		}
	}
	vector<ll> total_number_of_paths(n);
	for (int position = 0; position < n; position++)
	{
		for (int number_of_steps = 0; number_of_steps <= k; number_of_steps++)
		{
			total_number_of_paths[position] += dp[position][number_of_steps] * dp[position][k - number_of_steps];
			total_number_of_paths[position] %= mod;
		}
	}

	vector<ll> elements(n);
	for (size_t i = 0; i < n; i++)
		cin >> elements[i];
	
	ll sum = 0;
	for (size_t i = 0; i < n; i++)
	{
		sum += elements[i] * total_number_of_paths[i];
		sum %= mod;
	}

	for (size_t i = 0; i < query_count; i++)
	{
		int position; cin >> position;
		ll new_value; cin >> new_value;
		sum += (new_value - elements[position - 1]) * total_number_of_paths[position - 1];
		sum %= mod;
		elements[position-1] = new_value;

		cout << (sum+mod)%mod << "\n";
	}

	return 0;
}
