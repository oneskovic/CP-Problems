#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long

ll solution = 0;

void dfs(int parent, int current_index, const vector<vector<int>>& adj, vector<vector<int>>& dp)
{
	dp[current_index][0] = 1;
	for (int neighbor: adj[current_index])
	{
		if (neighbor != parent)
		{
			dfs(current_index, neighbor, adj, dp);
			for (size_t i = 0; i < dp[neighbor].size()-1; i++)
				dp[current_index][i + 1] += dp[neighbor][i];
		}
	}
	solution += dp[current_index].back();

	if (adj[current_index].size() <= 2 && parent != -1)
		return;


	int k = dp[1].size() - 1;
	ll combinations = 0;
	for (int neighbor: adj[current_index])
	{
		if (neighbor != parent)
		{
			for (int distance = 0; distance <= k-2; distance++)
			{
				int remaining_distance = k - distance - 2;
				combinations += dp[neighbor][distance] * (dp[current_index][remaining_distance + 1] - dp[neighbor][remaining_distance]);
			}
		}
	}
	solution += combinations / 2;
}



int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int node_count, required_distance;
	cin >> node_count >> required_distance;
	vector<vector<int>> adjacent(node_count+1);
	vector<vector<int>> dp(node_count + 1);
	for (size_t i = 0; i <= node_count; i++)
		adjacent[i] = vector<int>();
	for (size_t i = 0; i <= node_count; i++)
		dp[i] = vector<int>(required_distance + 1);

	for (size_t i = 0; i < node_count-1; i++)
	{
		int node1, node2;
		cin >> node1 >> node2;
		adjacent[node1].push_back(node2);
		adjacent[node2].push_back(node1);
	}
	dfs(-1,1, adjacent, dp);
	cout << solution;

	return 0;
}