#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
#define ll long long

int main()
{
	int n, m; cin >> n >> m;
	string s1, s2; cin >> s1 >> s2;
	vector<vector<ll>> dp(n+1, vector<ll>(m+1));

	ll solution = 0;
	for (size_t i = 1; i <= n; i++)
	{
		for (size_t j = 1; j <= m; j++)
		{
			dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) - 1;
			if (s1[i-1] == s2[j-1])
			{
				dp[i][j] = max(dp[i][j],max((ll)0, dp[i - 1][j - 1])+2);
			}
			solution = max(solution, dp[i][j]);
		}
	}
	cout << solution;
	return 0;
}