#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

void dfs_component(int node, const vector<vector<int>>& graph, vector<int>& component, int current_component)
{
	component[node] = current_component;
	for (int neighbor: graph[node])
		if (component[neighbor] == -1)
			dfs_component(neighbor, graph, component, current_component);
}

int find_node_in_cycle(int node, const vector<int>& dest, vector<bool>& visited)
{
	if (visited[node])
		return node;
	
	visited[node] = 1;
	return find_node_in_cycle(dest[node], dest, visited);
}

ll min_value_in_cycle(int current_node, int end_node, const vector<int>& dest, const vector<ll>& value)
{
	if (dest[current_node] == end_node)
		return value[current_node];

	return min(value[current_node], min_value_in_cycle(dest[current_node], end_node, dest, value));
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<int> dest(n);
	vector<vector<int>> graph(n, vector<int>());
	vector<ll> value(n);
	ll value_sum = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> dest[i] >> value[i];
		dest[i]--;
		value_sum += value[i];
		graph[i].push_back(dest[i]);
		graph[dest[i]].push_back(i);
	}

	vector<int> component(n, -1);
	vector<int> node_in_component;
	int current_component = 0;
	for (int i = 0; i < n; i++)
	{
		if (component[i] == -1)
		{
			dfs_component(i, graph, component, current_component++);
			node_in_component.push_back(i);
		}
	}

	vector<bool> visited(n);
	for (int component = 0; component < current_component; component++)
	{
		int x = find_node_in_cycle(node_in_component[component], dest, visited);
		ll min_val = min_value_in_cycle(x, x, dest, value);
		value_sum -= min_val;
	}
	cout << value_sum;
	return 0;
}