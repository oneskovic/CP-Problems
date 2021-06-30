#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<int> topological_sort(const vector<vector<int>>& graph)
{
	vector<int> in_degree(graph.size());
	for (int i = 0; i < graph.size(); i++)
	{
		for (int neighbor : graph[i])
		{
			in_degree[neighbor]++;
		}
	}
	vector<int> sorted_nodes; sorted_nodes.reserve(graph.size());
	for (int node = 0; node < graph.size(); node++)
		if (in_degree[node] == 0)
			sorted_nodes.push_back(node);
	
	for (int i = 0; i < graph.size(); i++)
	{
		int node = sorted_nodes[i];
		for (int neighbor: graph[node])
		{
			in_degree[neighbor]--;
			if (in_degree[neighbor] == 0)
				sorted_nodes.push_back(neighbor);
		}
	}
	return sorted_nodes;
}

vector<vector<bool>> fill_dp(const vector<vector<int>>& graph, const vector<int>& top_sort)
{
	vector<vector<bool>> dp(graph.size(), vector<bool>(2001));
	vector<int> in_degree(graph.size());
	for (int i = 0; i < graph.size(); i++)
	{
		for (int neighbor : graph[i])
			in_degree[neighbor]++;
	}

	for (int node: top_sort)
	{
		if (in_degree[node] == 0)
		{
			dp[node][0] = 1;
		}
		for (int neighbor: graph[node])
		{
			for (int i = 0; i < dp[node].size() - 1; i++)
			{
				if (dp[node][i] == 1)
				{
					dp[neighbor][i + 1] = 1;
				}
			}
		}
	}
	return dp;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n1, n2, m1, m2; cin >> n1 >> n2 >> m1 >> m2;
	vector<vector<int>> graph1(n1), graph2(n2);
	for (int i = 0; i < m1; i++)
	{
		int a, b; cin >> a >> b;
		a--; b--;
		graph1[a].push_back(b);
	}
	for (int i = 0; i < m2; i++)
	{
		int a, b; cin >> a >> b;
		a--; b--;
		graph2[a].push_back(b);
	}
	auto top_sort1 = topological_sort(graph1), top_sort2 = topological_sort(graph2);
	auto dp1 = fill_dp(graph1, top_sort1);
	auto dp2 = fill_dp(graph2, top_sort2);
	int query_cnt; cin >> query_cnt;
	for (int i = 0; i < query_cnt; i++)
	{
		int sum; cin >> sum;
		bool possible = false;
		for (int i = 0; i <= sum && !possible; i++)
		{
			if (dp1.back()[i] && dp2.back()[sum-i])
			{
				possible = 1;
			}
		}
		if (possible)
			cout << "Yes\n";
		else
			cout << "No\n";
	}

	return 0;
}