#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void dfs(int node, int current_component, const vector<vector<int>>& graph, vector<bool>& visited)
{
	visited[node] = 1;
	for (int neighbor: graph[node])
	{
		if (!visited[neighbor])
			dfs(neighbor, current_component, graph, visited);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	long long server_price, connection_price;
	cin >> server_price >> connection_price;
	int node_count, edge_count;
	cin >> node_count >> edge_count;
	
	vector<vector<int>> graph(node_count, vector<int>());
	for (size_t i = 0; i < edge_count; i++)
	{
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	if (server_price <= connection_price)
	{
		cout << server_price * node_count;
	}
	else
	{
		int component_count = 0;
		vector<bool> visited(node_count, 0);
		for (int node = 0; node < node_count; node++)
		{
			if (!visited[node])
				dfs(node, component_count++, graph, visited);
		}
		int non_server_nodes = node_count - component_count;
		int edges_to_connect = node_count - 1 - (component_count - 1);

		long long total_price = server_price * component_count + edges_to_connect * connection_price;
		cout << total_price;
	}

	return 0;
}
