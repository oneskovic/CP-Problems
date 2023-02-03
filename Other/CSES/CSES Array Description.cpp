#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n,m; cin >> n >> m;
	vector<int> elements(n);
	for (int i = 0; i < n; i++)
		cin >> elements[i];
	
	vector<vector<ll>> dp(n, vector<ll>(m+2));
	if (elements[0] == 0)
	{
		dp[0] = vector<ll>(m+2, 1);
		dp[0][0] = 0;
		dp[0].back() = 0;
	}
	else
		dp[0][elements[0]] = 1;

	for (int i = 1; i < n; i++)
	{
		int val = elements[i];
		if (val != 0)
		{
			dp[i][val] = dp[i - 1][val - 1] + dp[i-1][val] + dp[i - 1][val + 1];
			dp[i][val] %= mod;
		}
		else
		{
			for (int x = 1; x <= m; x++)
			{
				dp[i][x] = dp[i - 1][x - 1] + dp[i - 1][x] + dp[i - 1][x + 1];
				dp[i][x] %= mod;
			}
		}
	}
	ll sol = 0;
	for (int x : dp.back())
		sol = (sol + x) % mod;
	cout << sol;
	return 0;
}