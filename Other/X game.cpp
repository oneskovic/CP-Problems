#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main()
{
	int n; cin >> n;
	map<pair<int,int>, int> dp;
	dp[{1, 0}] = dp[{1, -1}] = dp[{1, -2}] = 1;
	dp[{2, 0}] = dp[{2, -1}] = dp[{2, -2}] = 2;

	for (int i = 1; i <= n; i++)
	{
		dp[{1, i}] = 2;
		if (dp[{2, i - 3}] == 1 || dp[{2, i - 4}] == 1 || dp[{2, i - 5}] == 1)
		{
			dp[{1, i}] = 1;
		}

		dp[{2, i}] = 1;
		if (dp[{1, i - 3}] == 2 || dp[{1, i - 4}] == 2 || dp[{1, i - 5}] == 2)
		{
			dp[{2, i}] = 2;
		}
	}
	for (int i = n; i > 0; i--)
	{
		cout << dp[{1, i}] << " ";
	}
	cout << "\n";
	for (int i = n; i > 0; i--)
	{
		cout << dp[{2, i}] << " ";
	}
	return 0;
}