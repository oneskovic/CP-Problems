#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	const ll mod = 1e9 + 7;
 
	int n, x; cin >> n >> x;
	vector<int> coin_values(n);
	for (int i = 0; i < n; i++)
		cin >> coin_values[i];
	vector<ll> dp(1e6 + 1, 0);
	for (int val : coin_values)
		dp[val] = 1;
	for (int sum = 0; sum <= x; sum++)
	{
		for (int val : coin_values)
		{
			if (sum - val >= 0)
				dp[sum] += dp[sum - val];
		}
		dp[sum] %= mod;
	}
	cout << dp[x];
 
 
	return 0;
}