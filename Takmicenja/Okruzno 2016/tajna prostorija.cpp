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
	vector<vector<int>> dp(10, vector<int>(n));
	for (size_t i = 0; i < n; i++)
	{
		for (int digit = 0; digit <= 9; digit++)
			dp[digit][i] = 0;
		
		ll number; cin >> number;
		while (number > 0)
		{
			int digit = number % 10;
			if (i > 0)
				dp[digit][i] = dp[digit][i - 1] + 1;
			else
				dp[digit][i] = 1;

			number /= 10;
		}
	}

	int max_len = 0;
	for (int digit = 0; digit <= 9; digit++)
		max_len = max(max_len, *max_element(dp[digit].begin(), dp[digit].end()));
	cout << max_len;

	return 0;
}