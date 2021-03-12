#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> lowest_reachable, dfs_indexes;
vector<pair<int,int>> directed_edges;
vector<bool> is_bridge;
vector<vector<int>> graph;

int dfs(int parent, int node, int dfs_index, vector<bool>& visited)
{
	directed_edges.emplace_back(parent, node);
	visited[node] = 1;
	int lowest = dfs_index;
	dfs_indexes[node] = dfs_index;

	for (int neighbor: graph[node])
	{
		if (!visited[neighbor])
		{
			int lowest_for_neighbor = dfs(node, neighbor, dfs_index + 1, visited);
			if (lowest_for_neighbor > dfs_index)
			{
				is_bridge[neighbor] = true;
			}
			lowest = min(lowest, lowest_for_neighbor);
		}
		else if (neighbor != parent) // back-edge
		{
			lowest = min(lowest, dfs_indexes[neighbor]);
			if (dfs_indexes[neighbor] < dfs_index)
			{
				directed_edges.emplace_back(node, neighbor);
			}
		}
	}

	lowest_reachable[node] = lowest;
	return lowest;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int node_count, edge_count; cin >> node_count >> edge_count;
	graph = vector<vector<int>>(node_count+1, vector<int>());
	for (size_t i = 0; i < edge_count; i++)
	{
		int a, b; cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	vector<bool> visited(node_count + 1);
	is_bridge = visited;
	lowest_reachable = vector<int>(node_count + 1, INT_MAX);
	dfs_indexes = vector<int>(node_count + 1);
	dfs(0, 1, 1, visited);

	if (find(is_bridge.begin(), is_bridge.end(), 1) != is_bridge.end())
	{
		cout << 0 << "\n";
		return 0;
	}

	for (int i = 1; i < directed_edges.size(); i++)
	{
		auto e = directed_edges[i];
		cout << e.first << " " << e.second << "\n";
	}

	return 0;
}