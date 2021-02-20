#include <algorithm>
#include <vector>
#include <iostream>
#include <stack>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int node_count, edge_count;
	cin >> node_count >> edge_count;
	vector<vector<int>> graph(node_count+1, vector<int>());
	for (size_t i = 0; i < edge_count; i++)
	{
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
	}

	int query_count; cin >> query_count;
	for (size_t i = 0; i < query_count; i++)
	{
		int node_from, node_to;
		cin >> node_from >> node_to;
		// Iterative dfs
		vector<bool> visited(node_count + 1);
		stack<int> s;
		s.push(node_from);
		while (!s.empty())
		{
			int current_node = s.top();
			visited[current_node] = true;
			s.pop();
			for (int neighbor: graph[current_node])
			{
				if (!visited[neighbor])
					s.push(neighbor);
			}
		}
		if (visited[node_to])
			cout << "da\n";
		else
			cout << "ne\n";
	}

	return 0;
}