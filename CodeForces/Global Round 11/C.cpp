#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct celebrity
{
	int x, y, t;
};

int distance(const celebrity& c1, const celebrity& c2)
{
	return abs(c1.x - c2.x) + abs(c1.y - c2.y);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int grid_size, celebrity_count; cin >> grid_size >> celebrity_count;
	celebrity_count++;
	vector<celebrity> celebrities(celebrity_count);
	celebrities[0] = { 1,1,0 };
	for (size_t i = 1; i < celebrity_count; i++)
		cin >> celebrities[i].t >> celebrities[i].x >> celebrities[i].y;
	
	vector<int> dp(celebrity_count);
	dp[0] = 1;
	int prefix = 0;
	for (int i = 1; i < celebrity_count; i++)
	{
		int max_prev_value = prefix;
		for (int j = max(0,i-2*grid_size); j < i; j++)
		{
			if (distance(celebrities[i], celebrities[j]) <= (celebrities[i].t - celebrities[j].t)
				&& dp[j] > 0)
			{
				max_prev_value = max(max_prev_value, dp[j]+1);
			}
		}
		dp[i] = max_prev_value;
		if (i >= 2*grid_size)
		{
			prefix = max(prefix, dp[i - 2*grid_size]+1);
		}
	}
	cout << *max_element(dp.begin(), dp.end()) - 1 <<"\n";
	return 0;
}