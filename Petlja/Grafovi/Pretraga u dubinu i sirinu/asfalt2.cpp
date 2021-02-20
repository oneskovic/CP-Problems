#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

#define DO_NOT_DELETE 0
#define DELETE_ALL_AFTER  1
#define DELETE_ALL_BEFORE 2

vector<int> node, next_node;
vector<int> should_delete;
vector<vector<int>> node_positions;
vector<vector<int>> strong_edges, weak_edges;
vector<bool> finished_node, enetered_node;


void dfs(int parent, int current_node)
{
	enetered_node[current_node] = 1;

	for (int neighbor : weak_edges[current_node])
	{
		if (enetered_node[neighbor])
		{
			if (finished_node[neighbor]) // Cross-edge
			{
				should_delete[neighbor] = DELETE_ALL_AFTER;
			}
			else // Back-edge
			{
				should_delete[neighbor] = DELETE_ALL_BEFORE;
				for (int neighbor_child: strong_edges[neighbor])
				{
					if (finished_node[neighbor_child] || !enetered_node[neighbor_child])
					{
						should_delete[neighbor_child] = DELETE_ALL_AFTER;
					}
				}
			}
			should_delete[current_node] = DELETE_ALL_AFTER;
		}
	}

	for (int neighbor : strong_edges[current_node])
	{
		if (neighbor != parent)
		{
			node.push_back(current_node);
			next_node.push_back(neighbor);
			node_positions[current_node].push_back(node.size() - 1);
			dfs(current_node, neighbor);
		}
	}

	if (strong_edges[current_node].size() == 1)
	{
		node.push_back(current_node);
		next_node.push_back(-1);
		node_positions[current_node].push_back(node.size() - 1);
	}

	finished_node[current_node] = true;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int node_count, edge_count;
	cin >> node_count >> edge_count;
	strong_edges = vector<vector<int>>(node_count + 1, vector<int>());
	weak_edges = vector<vector<int>>(node_count + 1, vector<int>());
	for (size_t i = 0; i < edge_count; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		if (c)
		{
			strong_edges[a].push_back(b);
			strong_edges[b].push_back(a);
		}
		else
		{
			weak_edges[a].push_back(b);
			weak_edges[b].push_back(a);
		}
	}
	
	node_positions = vector<vector<int>>(node_count + 1, vector<int>());
	finished_node = vector<bool>(node_count + 1);
	enetered_node = finished_node;
	should_delete = vector<int>(node_count + 1, DO_NOT_DELETE);
	dfs(-1, 1);

	vector<int> solution;
	for (int i = node.size() - 1; i >= 0; i--)
	{
		int parent = node[i];
		int child = next_node[i];
		if (should_delete[child] == DELETE_ALL_BEFORE)
		{
			should_delete[parent] = DELETE_ALL_BEFORE;
			for (int parent_neighbor : strong_edges[parent])
			{
				if (parent_neighbor != child)
				{
					should_delete[parent_neighbor] = DELETE_ALL_AFTER;
				}
			}
		}
	}

	for (size_t i = 0; i < node.size(); i++)
	{
		int current_node = node[i];
		if (should_delete[current_node] == DELETE_ALL_AFTER)
		{
			int child = next_node[i];
			if (child != -1)
			{
				should_delete[child] = DELETE_ALL_AFTER;
			}
		}
	}

	for (size_t i = 0; i < node.size(); i++)
		if (should_delete[node[i]] == DO_NOT_DELETE)
			solution.push_back(node[i]);

	sort(solution.begin(), solution.end());
	solution.erase(unique(solution.begin(), solution.end()),solution.end());

	cout << solution.size() << "\n";
	for (int i: solution)
		cout << i << " ";

	return 0;
}