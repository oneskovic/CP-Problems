#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long

int main()
{

	vector<vector<int>> divisors(100002);
	for (size_t i = 1; i < divisors.size(); i++)
	{
		for (size_t j = i+i; j < divisors.size(); j+=i)
		{
			divisors[j].push_back(i);
		}
	}

	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		vector<ll> sizes(n+1);
		vector<ll> dp(n+1);
		for (size_t i = 0; i < n; i++)
		{
			ll index = i + 1;
			cin >> sizes[index];
			// Check all possible indices with which the current index can connect
			// i.e all indices that divide the current index
			ll max_value = 1;
			for(ll divisor: divisors[index])
			{
				if (index % divisor == 0 && sizes[divisor] < sizes[index])
				{
					max_value = max(max_value, dp[divisor]+1);
				}
				divisor++;
			}
			dp[index] = max_value;
		}
		cout << *max_element(dp.begin(), dp.end()) << "\n";
	}
	return 0;
}