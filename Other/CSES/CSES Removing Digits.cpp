#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<int> dp(n+1, 1000000);
	dp[0] = 0;
	for (int x = 1; x <= n; x++)
	{
		int x_cpy = x;
		while (x_cpy > 0)
		{
			int digit = x_cpy % 10;
			if (x - digit >= 0)
				dp[x] = min(dp[x], dp[x - digit]+1);
			x_cpy /= 10;
		}
	}
	cout << dp[n];

	return 0;
}