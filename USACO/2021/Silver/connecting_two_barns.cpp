#include <algorithm>
#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;
typedef long long ll;

void dfs(int node, const vector<vector<int>>& graph, vector<int>& component, int current_component)
{
	component[node] = current_component;
	for (int neighbor: graph[node])
		if (component[neighbor] == -1)
			dfs(neighbor, graph, component, current_component);
}

ll get_cost(ll node1, ll node2)
{
	node1++; node2++;
	return (node1 - node2) * (node1 - node2);
}

vector<ll> shortest_path_from_components(int target_component, const vector<vector<int>>& graph, const vector<int>& component)
{
	int n = graph.size();
	vector<int> target_component_nodes;
	for (int node = 0; node < n; node++)
		if (component[node] == target_component)
			target_component_nodes.push_back(node);

	int component_cnt = *max_element(component.begin(), component.end()) + 1;
	
	vector<ll> solution(component_cnt, LLONG_MAX);
	solution[target_component] = 0;
	for (int node = 0; node < n; node++)
	{
		auto it1 = lower_bound(target_component_nodes.begin(), target_component_nodes.end(), node);
		ll cost1 = (it1 == target_component_nodes.end() ? LLONG_MAX : get_cost(node, *it1));
		ll cost2 = (it1 == target_component_nodes.begin() ? LLONG_MAX : get_cost(node, *(--it1)));
		ll min_cost = min(cost1, cost2);
		solution[component[node]] = min(solution[component[node]], min_cost);
	}
	return solution;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n, m; cin >> n >> m;
		vector<vector<int>> graph(n, vector<int>());
		for (int i = 0; i < m; i++)
		{
			int a, b; cin >> a >> b;
			a--; b--;
			graph[a].push_back(b);
			graph[b].push_back(a);
		}
		vector<int> components(n,-1);
		int component_cnt = 0;
		for (int i = 0; i < n; i++)
			if (components[i] == -1)
				dfs(i, graph, components, component_cnt++);
		
		if (components.back() == 0)
		{
			cout << 0 << "\n";
		}
		else
		{
			auto paths_from_start = shortest_path_from_components(0, graph, components);
			auto paths_to_end = shortest_path_from_components(components.back(), graph, components);
			ll solution = LLONG_MAX;
			for (int component = 0; component < component_cnt; component++)
			{
				ll cost = paths_from_start[component] + paths_to_end[component];
				solution = min(solution, cost);
			}
			cout << solution << "\n";
		}
	}

	return 0;
}