#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;
typedef long long ll;

ll solve(const vector<int>& elements)
{
	const ll mod = 998244353;
	int n = elements.size();
	// dp[i] represents all valid subarrays such that mex = i
	// dp[i][0] represents all valid subarrays such that mex = i and the subarray doesnt contain i+1
	// dp[i][1] all valid subarrays mex = i that contain i+1
	vector<vector<ll>> dp(elements.size() + 5,vector<ll>(2));
	ll solution = 0;
	for (int i = 0; i < n; i++)
	{
		int val = elements[i];
		if (val == 0 || val == 1)
			solution++; // subarray {0} or {1} is valid by itself

		solution += dp[val + 1][0] + dp[val+1][1];
		solution += dp[val][0];
		if (val > 0)
			solution += dp[val - 1][0] + dp[val-1][1];

		solution %= mod;

		dp[val + 1][0] = (2 * dp[val + 1][0]) % mod;
		dp[val + 1][1] = (2 * dp[val + 1][1]) % mod;

		if (val > 0)
		{
			dp[val - 1][1] = (2 * dp[val - 1][1] + dp[val - 1][0]) % mod;
		}
		dp[val + 1][0] += dp[val][0];
		dp[val + 1][0] %= mod;

		if (val == 0)
			dp[1][0]++;
		
		if (val == 1)
			dp[0][1]++;
		
	}
	return solution%mod;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<int> elements(n);
		for (int i = 0; i < n; i++)
			cin >> elements[i];
		
		cout << solve(elements) << "\n";
	}

	return 0;
}