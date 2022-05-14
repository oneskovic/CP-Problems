#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<int> elements(n);
	for (int i = 0; i < n; i++)
		cin >> elements[i];
	int maxsum = accumulate(elements.begin(), elements.end(), 0);
	vector<bool> dp(maxsum + 1);
	vector<bool> prev_dp = dp;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= maxsum - elements[i]; j++)
		{
			dp[j + elements[i]] = prev_dp[j + elements[i]] || prev_dp[j];
		}
		dp[elements[i]] = 1;
		prev_dp = dp;
	}

	int cnt = 0;
	for (int i = 0; i <= maxsum; i++)
		cnt += dp[i];
	cout << cnt << "\n";
	for (int i = 0; i <= maxsum; i++)
		if (dp[i])
			cout << i << " ";
	
	cout << "\n";
	return 0;
}