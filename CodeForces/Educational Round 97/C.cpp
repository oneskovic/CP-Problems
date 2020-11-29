#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long

int main()
{
	ios::sync_with_stdio(false);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		vector<int> optimal_cooking_time(n);
		for (size_t i = 0; i < n; i++)
		{
			cin >> optimal_cooking_time[i];
			optimal_cooking_time[i]--;
		}
		sort(optimal_cooking_time.begin(), optimal_cooking_time.end());

		// dp[i][j] -> f(position, time)
		vector<vector<int>> dp(n);
		for (size_t i = 0; i < n; i++)
			dp[i] = vector<int>(2 * n, 0);
		
		dp[0][0] = optimal_cooking_time[0];
		for (int i = 1; i < 2 * n; i++)
			dp[0][i] = min(dp[0][i - 1], abs(optimal_cooking_time[0] - i));

		for (int position = 1; position < n; position++)
		{
			for (int time = position; time < 2*n; time++)
			{
				int current_penalty = abs(time - optimal_cooking_time[position]);
				if (time > position)
					dp[position][time] = min(dp[position - 1][time - 1] + current_penalty, dp[position][time - 1]);
				else
					dp[position][time] = dp[position - 1][time - 1] + current_penalty;
			}
		}
		cout << dp[n - 1][2 * n - 1] << "\n";
	}
	return 0;
}