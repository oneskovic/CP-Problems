#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

void dfs(int node, int boot_index, vector<vector<int>>& min_changes_to_end, const vector<int>& boot_distance, const vector<int>& boot_strength, const vector<int>& snow_ammount)
{
	if (min_changes_to_end[boot_index][node] != -1)
		return;
	
	int n = snow_ammount.size();
	int m = boot_strength.size();
	int sol = 1000;
	if (snow_ammount[node] <= boot_strength[boot_index])
	{
		for (int d = 1; d <= boot_distance[boot_index] && node+d < n; d++)
		{
			if (snow_ammount[node+d] <= boot_strength[boot_index])
			{
				dfs(node + d, boot_index, min_changes_to_end, boot_distance, boot_strength, snow_ammount);
				sol = min(sol, min_changes_to_end[boot_index][node + d]);
			}
		}
	}
	if (boot_index + 1 < m)
	{
		dfs(node, boot_index + 1, min_changes_to_end, boot_distance, boot_strength, snow_ammount);
		sol = min(sol, min_changes_to_end[boot_index + 1][node] + 1);
	}
	min_changes_to_end[boot_index][node] = sol;
}

int main()
{
	freopen("snowboots.in", "r", stdin);
	freopen("snowboots.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m; cin >> n >> m;
	vector<int> snow_ammount(n);
	for (int i = 0; i < n; i++)
		cin >> snow_ammount[i];
	vector<int> boot_strength(m);
	vector<int> boot_distance(m);
	for (int i = 0; i < m; i++)
		cin >> boot_strength[i] >> boot_distance[i];
	
	vector<vector<int>> min_changes_to_end(m, vector<int>(n, -1));
	for (int i = 0; i < m; i++)
		min_changes_to_end[i][n - 1] = 0;
	dfs(0, 0, min_changes_to_end, boot_distance, boot_strength, snow_ammount);
	
	cout << min_changes_to_end[0][0];
	return 0;
}