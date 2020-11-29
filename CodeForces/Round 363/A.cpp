#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// 0 - do nothing
// 1 - write code
// 2 - go to the gym
vector<vector<int>> available_activities =
{
	{0},{0,1},{0,2},{0,1,2}
};

vector<vector<int>> dp;

int find_min(int previous_activity, int day_index, const vector<int>& days)
{
	if (day_index == days.size())
		return 0;

	if (previous_activity != -1 && dp[previous_activity][day_index] != -1)
		return dp[previous_activity][day_index];
	
	int min_result = INT_MAX;
	for (int activity: available_activities[days.at(day_index)])
	{
		if (previous_activity == activity && activity != 0)
			continue;
		
		int result = find_min(activity, day_index + 1, days);
		if (activity == 0)
			result++;
		min_result = min(min_result, result);
	}
	if (previous_activity != -1)
		dp[previous_activity][day_index] = min_result;

	return min_result;
}

int main()
{
	int n; cin >> n;
	vector<int> days(n);
	for (size_t i = 0; i < n; i++)
		cin >> days[i];
	dp = vector<vector<int>>(3);
	for (size_t i = 0; i < 3; i++)
		dp[i] = vector<int>(n,-1);

	cout << find_min(-1, 0, days);
	return 0;
}