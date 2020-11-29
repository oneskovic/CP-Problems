#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int tests_count; cin >> tests_count;
	for (size_t test_no = 0; test_no < tests_count; test_no++)
	{
		int n; cin >> n;
		vector<bool> is_hard(n+1);
		for (size_t i = 0; i < n; i++)
		{
			int temp; cin >> temp;
			is_hard[i] = temp;
		}
		vector<int> dp(n+4);
		
		for (int i = n-1; i >= 0; i--)
		{
			int defeat_one_boss = min(dp[i + 2], dp[i + 3]) + is_hard[i];
			int defeat_two_bosses = min(dp[i + 3], dp[i + 4]) + is_hard[i] + is_hard[i+1];
			dp[i] = min(defeat_one_boss, defeat_two_bosses);
		}
		cout << dp[0] << "\n";
	}
	return 0;
}