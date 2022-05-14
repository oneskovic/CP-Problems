#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
typedef long long ll;

void print_dp(const vector<vector<int>>& m)
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << setfill('0') << setw(2) << m[i][j] << " ";
		}
		cout << "\n";
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int capacity, n; cin >> capacity >> n;
	vector<vector<pair<int,int>>> temp(2001,vector<pair<int,int>>());
	for (int i = 0; i < n; i++)
	{
		int value, weight, cnt; cin >> value >> weight >> cnt;
		temp[weight].push_back({ value,cnt });
	}
	for (int w = 0; w < temp.size(); w++)
		sort(temp[w].begin(), temp[w].end(),greater<pair<int,int>>());
	vector<vector<int>> equal_weight_items(2001, vector<int>());
	for (int w = 0; w < temp.size(); w++)
	{
		int added_cnt = 0;
		for (auto item: temp[w])
		{
			for (int i = 0; i < item.second && added_cnt < 2000; i++, added_cnt++)
				equal_weight_items[w].push_back(item.first);
			if (added_cnt == 2000)
				break;
		}
	}
	vector<vector<int>> dp(2001, vector<int>(2001, 0));
	for (int cap = 1; cap <= capacity; cap++)
	{
		for (int w = 1; w < equal_weight_items.size(); w++)
		{
			int remaining_capacity = cap;
			int added_val = 0;
			dp[cap][w] = dp[cap][w-1];
			for (int val: equal_weight_items[w])
			{
				remaining_capacity -= w;
				added_val += val;
				if (remaining_capacity < 0)
					break;
				dp[cap][w] = max(dp[cap][w], dp[remaining_capacity][w - 1] + added_val);
			}
		}
	}
	cout << *max_element(dp[capacity].begin(), dp[capacity].end());

	return 0;
}