#include <algorithm>
#include <iostream>
#include <limits.h>
#include <vector>
#include <tuple>
#include <queue>
using namespace std;

/// <summary>
/// Finds the smallest cycle containing the given node:
/// Perform a bfs to find all shortest paths from the given node
/// While performing the bfs compute the cycle length formed by each "cross" edge
/// For example: when finding a cycle that contains the node 3, a cycle must contain
/// an edge u,v where u != v != 3, then the cycle is:
/// 3 -> u -> v -> 3, length of which is: shortest_path[u] + shortest_path[v] + 1
/// </summary>
int min_cycle_containing_node(int node, const vector<vector<int>>& graph)
{
	vector<int> shortest_path(graph.size()); // shortest_path[node] = 0
	vector<bool> visited(graph.size());

	int shortest_cycle = INT_MAX;
	queue<tuple<int, int, int>> bfs_queue; bfs_queue.emplace(-1, node, 0);
	visited[node] = 1;

	while (!bfs_queue.empty())
	{
		int parent = get<0>(bfs_queue.front());
		int current_node = get<1>(bfs_queue.front());
		int current_dist = get<2>(bfs_queue.front());
		bfs_queue.pop();

		for (int neighbor: graph[current_node])
		{
			if (neighbor == parent)
				continue;
			if (visited[neighbor])
			{
				// Both shortest_path[current_node] and shortest_path[neighbor] are calculated at this point
				int current_cycle = shortest_path[current_node] + shortest_path[neighbor] + 1;
				shortest_cycle = min(current_cycle, shortest_cycle);
			}
			else
			{
				bfs_queue.emplace(current_node, neighbor, current_dist + 1);
				visited[neighbor] = 1;
				shortest_path[neighbor] = current_dist + 1;
			}
		}
	}
	return shortest_cycle;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int node_cnt, edge_cnt; cin >> node_cnt >> edge_cnt;
	vector<vector<int>> graph(node_cnt + 1, vector<int>());
	for (int i = 0; i < edge_cnt; i++)
	{
		int a, b; cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	int minimal_cycle_len = INT_MAX;
	for (int node = 1; node <= node_cnt; node++)
		minimal_cycle_len = min(minimal_cycle_len, min_cycle_containing_node(node,graph));
	
	if (minimal_cycle_len == INT_MAX)
		cout << "-1" << endl;
	else
		cout << minimal_cycle_len << endl;
	
	return 0;
}