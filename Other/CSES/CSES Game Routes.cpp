#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef long long ll;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	const ll mod = 1e9 + 7;

	int node_cnt, edge_cnt; cin >> node_cnt >> edge_cnt;
	vector<vector<int>> graph(node_cnt, vector<int>());
	vector<int> in_degree(node_cnt);
	for (int i = 0; i < edge_cnt; i++)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
		in_degree[b]++;
	}
	queue<int> zero_degree_nodes;
	for (int i = 0; i < node_cnt; i++)
		if (in_degree[i] == 0)
			zero_degree_nodes.push(i);
	
	vector<ll> dp(node_cnt);
	dp[0] = 1;
	while (!zero_degree_nodes.empty())
	{
		int node = zero_degree_nodes.front();
		zero_degree_nodes.pop();
		dp[node] %= mod;
		for (int neighbor: graph[node])
		{
			in_degree[neighbor]--;
			if (in_degree[neighbor] == 0)
				zero_degree_nodes.push(neighbor);
			dp[neighbor] += dp[node];
		}
	}
	cout << dp.back() << "\n";

	return 0;
}