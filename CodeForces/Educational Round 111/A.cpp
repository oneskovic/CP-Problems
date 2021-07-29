#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int solve(int sum_to_reach, int current_sum, int current_number, int cnt)
{
	if (sum_to_reach < current_sum)
	{
		return INT_MAX/2;
	}
	if (sum_to_reach == current_sum)
	{
		return cnt;
	}
	int result = INT_MAX;
	for (int i = 1; i <= 2; i++)
	{
		int temp = min(solve(sum_to_reach,current_sum+current_number*i,current_number+1,cnt+i), solve(sum_to_reach, current_sum + current_number * i, current_number + 2, cnt + i));
		result = min(temp, result);
	}
	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_cnt; cin >> test_cnt;
	vector<vector<int>> dp(5001, vector<int>(5001, INT_MAX/2));
	dp[1][1] = 1;
	dp[1][2] = 2;
	for (int number = 2; number <= 5000; number++)
	{
		for (int sum = 1; sum <= 5000; sum++)
		{
			for (int i = 1; i <= 2; i++)
			{
				if (sum - number*i > 0)
				{
					dp[number][sum] = min(dp[number][sum],dp[number-1][sum - number * i] + i);
					dp[number][sum] = min(dp[number][sum], dp[number - 2][sum - number * i] + i);
				}
			}
		}
	}
	

	while (test_cnt--)
	{
		int s; cin >> s;
		int solution = INT_MAX;
		for (int number = 0; number <= 5000; number++)
		{
			solution = min(solution, dp[number][s]);
		}
		cout << solution << "\n";

	}
	return 0;
}