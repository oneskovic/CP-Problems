#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <numeric>
using namespace std;
#define ll long long

pair<int, int> cycle_edge;
bool dfs_cycle(int parent, int index, const vector<vector<int>>& adj, vector<bool>& visited, unordered_set<int>& cycle)
{
	visited[index] = true;
	for (int adj_node: adj[index])
	{
		if (adj_node == parent)
			continue;
		if (visited[adj_node])
		{
			cycle.insert(adj_node);
			cycle.insert(index);
			cycle_edge = { index,adj_node };
			return true;
		}
		else
		{
			if (dfs_cycle(index,adj_node,adj,visited,cycle) && cycle.find(-2) == cycle.end())
			{
				cycle.insert(index);
				if (cycle.find(parent) != cycle.end())
					cycle.insert(-2);
				return true;
			}
		}
	}
	return false;
}

int dfs_count_paths(int parent, int index, const vector<vector<int>>& adj)
{
	int count = 0;
	for (int adj_node: adj[index])
	{
		if (adj_node != parent)
		{
			int child_count = dfs_count_paths(index, adj_node, adj);
			count += 2 * child_count + 1;
		}
	}
	return count;
}

int count_paths(const vector<vector<int>>& adjacent)
{
	return dfs_count_paths(-1,1, adjacent);
}

int count_cycle(const vector<vector<int>>& adjacent)
{
	unordered_set<int> nodes_in_cycle;
	vector<bool> visited(adjacent.size());
	dfs_cycle(-1, 1, adjacent, visited, nodes_in_cycle);
	return nodes_in_cycle.size()-1; // subtract 1 (the "-2" node)
}

void erase_from_vector(vector<int>& v, int element)
{
	auto it = find(v.begin(), v.end(), element);
	v.erase(it);
}

int main()
{
	ios::sync_with_stdio(false);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		vector<vector<int>> adjacent(n+1);
		for (size_t i = 0; i < n; i++)
		{
			int a, b;
			cin >> a >> b;
			adjacent[a].push_back(b);
			adjacent[b].push_back(a);
		}
		int solution = count_cycle(adjacent);

		// Remove the cycle
		erase_from_vector(adjacent[cycle_edge.first], cycle_edge.second);
		erase_from_vector(adjacent[cycle_edge.second], cycle_edge.first);

		solution += count_paths(adjacent);

		cout << solution << "\n";
	}
	return 0;
}