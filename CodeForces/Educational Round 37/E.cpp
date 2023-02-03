#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;

int dfs(int node, const set<pair<int, int>>& removed_edges, set<int>& unvisited_nodes)
{
	unvisited_nodes.erase(node);
	auto it = unvisited_nodes.begin();
	int sol = 1;
	while (it != unvisited_nodes.end())
	{
		if (removed_edges.find({ node,*it }) != removed_edges.end())
		{
			it++;
			continue;
		}
		int current_node = *it;
		sol += dfs(current_node, removed_edges, unvisited_nodes);
		it = lower_bound(unvisited_nodes.begin(), unvisited_nodes.end(), current_node);
	}
	return sol;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m; cin >> n >> m;
	set<pair<int,int>> removed_edges;
	for (int i = 0; i < m; i++)
	{
		int a, b; cin >> a >> b;
		a--; b--;
		removed_edges.insert({ a,b });
		removed_edges.insert({ b,a });
	}
	set<int> unvisited_nodes;
	for (int i = 0; i < n; i++)
		unvisited_nodes.insert(i);
	
	int component_cnt = 0;
	vector<int> component_sizes;
	while (!unvisited_nodes.empty())
	{
		int comp_size = dfs(*unvisited_nodes.begin(), removed_edges, unvisited_nodes);
		component_sizes.push_back(comp_size);
		component_cnt++;
	}
	cout << component_cnt << "\n";
	sort(component_sizes.begin(), component_sizes.end());
	for (int i = 0; i < component_cnt; i++)
	{
		cout << component_sizes[i] << " ";
	}
	return 0;
}