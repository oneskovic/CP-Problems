#include <algorithm>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <vector>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7;

int fastmod(int x)
{
	if (x >= mod)
		x -= mod;
	if (x >= mod)
		x -= mod;
	return x;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	int maxsum = n * (n + 1) / 2;
	if (maxsum % 2 != 0)
	{
		cout << "0\n";
		return 0;
	}
	maxsum /= 2;
	
	vector<vector<int>> dp(n + 1, vector<int>(maxsum + 1));
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= maxsum; j++)
		{
			dp[i][j] = dp[i - 1][j];
			if (j - i >= 0)
			{
				dp[i][j] += dp[i - 1][j - i];
				dp[i][j] = fastmod(dp[i][j]);
			}
		}
	}
	ll res = dp[n][maxsum] * (ll)500000004;
	cout << res % mod << "\n";
	return 0;
}