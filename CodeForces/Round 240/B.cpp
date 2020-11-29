#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long
vector<vector<int>> divisors;
constexpr ll M = 1e9 + 7;

vector<vector<ll>> dp;

ll count_sequences(int length, int current_number)
{
	if (length == 0)
		return 1;
	if (dp[length][current_number] != -1)
		return dp[length][current_number];

	ll count = 0;
	for (int next_number: divisors[current_number])
	{
		count += (count_sequences(length - 1, next_number) % M);
		count %= M;
	}
	dp[length][current_number] = count;
	return count;
}

int main()
{
	int max_value, length; cin >> max_value >> length;
	divisors = vector<vector<int>>(max_value+1);
	for (size_t i = 1; i <= max_value; i++)
		for (size_t j = i; j <= max_value; j+=i)
			divisors[j].push_back(i);

	dp = vector<vector<ll>>(length + 1);
	for (size_t i = 0; i < length; i++)
		dp[i] = vector<ll>(max_value+1,-1);

	ll total_count = 0;
	for (size_t i = 1; i <= max_value; i++)
		total_count += (count_sequences(length - 1, i) % M);
	
	cout << total_count % M;
	return 0;
}