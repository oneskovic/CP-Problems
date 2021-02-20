#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int node_count, edge_count; cin >> node_count >> edge_count;
	auto graph = vector<vector<int>>(node_count, vector<int>());
	for (size_t i = 0; i < edge_count; i++)
	{
		int a, b; cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	vector<int> component(node_count, -1);
	int component_number = 0;
	for (size_t i = 0; i < node_count; i++)
	{
		// Iterative dfs
		stack<int> nodes_to_process;
		if (component[i] == -1)
		{
			nodes_to_process.push(i);
			component_number++;
		}
		while (!nodes_to_process.empty())
		{
			int current_node = nodes_to_process.top();
			nodes_to_process.pop();
			component[current_node] = component_number;

			for (int neighbor: graph[current_node])
			{
				if (component[neighbor] == -1)
				{
					nodes_to_process.push(neighbor);
				}
			}
		}
	}
	for (int i: component)
	{
		cout << i << " ";
	}
	return 0;
}