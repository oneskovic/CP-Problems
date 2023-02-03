#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int temp_sol = 0;
	for (int i = 0; i <= 9; i++)
	{
		for (int j = 0; j <= 11; j++)
		{
			for (int k = 0; k <= 7; k++)
			{
				int s = i - j + k;
				if (s >= 0)
				{
					temp_sol++;
				}
			}
		}
	}

	int n; cin >> n;
	vector<int> limits(n);
	for (int i = 0; i < n; i++)
		cin >> limits[i];

	int max_sum = 10;
	vector<map<int, int>> dp(n, map<int, int>());
	for (int h = 0; h <= limits[0]; h++)
	{
		dp[0][h] = 1;
	}
	for (int i = 1; i < n; i++)
	{
		if (i % 2 == 1)
		{
			for (int sum = -max_sum; sum <= max_sum; sum++)
			{
				for (int h = 0; h <= limits[i]; h++)
				{
					dp[i][sum] += dp[i - 1][sum + h];
				}
			}
		}
		else
		{
			for (int sum = -max_sum; sum <= max_sum; sum++)
			{
				for (int h = 0; h <= limits[i]; h++)
				{
					dp[i][sum] += dp[i - 1][sum - h];
				}
			}
		}
	}
	int sol = 0;
	for (auto kvp: dp.back())
	{
		if (kvp.first >= 0)
		{
			sol += kvp.second;
		}
	}
	cout << sol;

	return 0;
}