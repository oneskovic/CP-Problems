#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7;
int fastmod(int x)
{
	if (x > mod)
		x -= mod;
	if (x > mod)
		x -= mod;
	return x;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, x; cin >> n >> x;
	vector<int> coin_values(n);
	for (int i = 0; i < n; i++)
		cin >> coin_values[i];
	vector<int> dp(x + 1, 0);
	dp[0] = 1;
	for (int i = 0; i < n; i++)
	{
		int coin_val = coin_values[i];
		for (int sum = 1; sum <= x; sum++)
		{
			dp[sum] += (sum - coin_val >= 0) ? dp[sum - coin_val]: 0;	
			dp[sum] = fastmod(dp[sum]);
		}
	}
	cout << dp[x]%mod;

	return 0;
}
