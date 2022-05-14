#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int n, max_price; cin >> n >> max_price;
	vector<int> prices(n);
	for (int i = 0; i < n; i++)
		cin >> prices[i];
	vector<int> page_cnt(n);
	for (int i = 0; i < n; i++)
		cin >> page_cnt[i];
	vector<vector<int>> dp(n + 1, vector<int>(max_price+1));
	for (int i = 1; i <= n; i++)
	{
		for (int price = 1; price <= max_price; price++)
		{
			dp[i][price] = dp[i - 1][price];
			if (price >= prices[i - 1])
				dp[i][price] = max(dp[i][price], dp[i - 1][price - prices[i - 1]] + page_cnt[i - 1]);
		}
	}
	cout << dp[n][max_price];
	return 0;
}