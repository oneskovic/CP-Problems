#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct point
{
	int x, y;
};

void dfs(int node, int component_id, vector<int>& components, const vector<vector<int>>& graph)
{
	components[node] = component_id;
	for (int neighbor: graph[node])
	{
		if (components[neighbor] == -1)
		{
			dfs(neighbor, component_id, components, graph);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	freopen("fenceplan.in", "r", stdin); 
	freopen("fenceplan.out", "w", stdout);

	int node_count, edge_count;
	cin >> node_count >> edge_count;
	vector<point> nodes(node_count + 1);
	for (size_t i = 1; i <= node_count; i++)
		cin >> nodes[i].x >> nodes[i].y;
	
	vector<vector<int>> graph(node_count + 1, vector<int>());

	for (size_t i = 0; i < edge_count; i++)
	{
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	
	vector<int> components(node_count + 1, -1);
	int component_id = 0;
	for (int node = 1; node <= node_count; node++)
	{
		if (components[node] == -1)
		{
			dfs(node, component_id, components, graph);
			component_id++;
		}
	}
	
	vector<pair<int, int>> max_xy_in_component(component_id, { INT_MIN,INT_MIN });
	vector<pair<int, int>> min_xy_in_component(component_id, { INT_MAX,INT_MAX });
	for (int node = 1; node <= node_count; node++)
	{
		int node_x = nodes[node].x;
		int node_y = nodes[node].y;
		int node_component = components[node];

		max_xy_in_component[node_component].first = max(max_xy_in_component[node_component].first, node_x);
		max_xy_in_component[node_component].second = max(max_xy_in_component[node_component].second, node_y);
		
		min_xy_in_component[node_component].first = min(min_xy_in_component[node_component].first, node_x);
		min_xy_in_component[node_component].second = min(min_xy_in_component[node_component].second, node_y);
	}

	int min_perimeter = INT_MAX;
	for (int component = 0; component < max_xy_in_component.size(); component++)
	{
		int dx = max_xy_in_component[component].first - min_xy_in_component[component].first;
		int dy = max_xy_in_component[component].second - min_xy_in_component[component].second;
		int perimeter = 2 * (dx+dy);
		min_perimeter = min(perimeter, min_perimeter);
	}
	cout << min_perimeter;

	return 0;
}