#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#include <limits.h>
using namespace std;

vector<int> low, high;


void dfs(int node, vector<bool>& visited, const vector<vector<int>>& graph)
{
	visited[node] = 1;
	for (int neighbor: graph[node])
	{
		if (!visited[neighbor])
		{
			dfs(neighbor, visited, graph);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int node_count, edge_count;
	cin >> node_count >> edge_count;
	auto graph = vector<vector<int>>(node_count + 1, vector<int>());
	auto transpose_graph = graph;
	for (size_t i = 0; i < edge_count; i++)
	{
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		transpose_graph[b].push_back(a);
	}

	vector<bool> visited(node_count + 1);
	dfs(1, visited, graph);
	for (size_t i = 1; i <= node_count; i++)
	{
		if (!visited[i])
		{
			cout << "NO\n";
			cout << 1 << " " << i << "\n";
			return 0;
		}
	}

	visited = vector<bool>(node_count + 1);
	dfs(1, visited, transpose_graph);
	for (size_t i = 1; i <= node_count; i++)
	{
		if (!visited[i])
		{
			cout << "NO\n";
			cout << i << " " << 1 << "\n";
			return 0;
		}
	}
	cout << "YES\n";

	return 0;
}