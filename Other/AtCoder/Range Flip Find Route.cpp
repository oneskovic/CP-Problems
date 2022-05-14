#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <limits.h>
using namespace std;
typedef long long ll;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m; cin >> n >> m;
	vector<vector<bool>> mat(n, vector<bool>(m));
	for (int i = 0; i < n; i++)
	{
		string s; cin >> s;
		for (int j = 0; j < m; j++)
			mat[i][j] = (s[j] == '.');
	}
	vector<vector<int>> dp(n, vector<int>(m));
	dp[0][0] = (mat[0][0] == 0);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (i == 0 && j == 0)
				continue;
			
			dp[i][j] = INT_MAX;
			if (i - 1 >= 0)
			{
				if (mat[i][j] == 1)
					dp[i][j] = min(dp[i][j], dp[i - 1][j]);
				else
					dp[i][j] = min(dp[i][j], dp[i - 1][j] + (mat[i-1][j] != mat[i][j]));
			}
			if (j-1 >= 0)
			{
				if (mat[i][j] == 1)
					dp[i][j] = min(dp[i][j], dp[i][j-1]);
				else
					dp[i][j] = min(dp[i][j], dp[i][j-1] + (mat[i][j-1] != mat[i][j]));
			}
		}
	}
	cout << dp.back().back() << "\n";

	return 0;
}
