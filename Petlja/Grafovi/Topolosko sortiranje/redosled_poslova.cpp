#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m; cin >> n >> m;
	auto degree = vector<int>(n);
	auto nodes_that_depend_on = vector<vector<int>>(n, vector<int>());
	for (size_t i = 0; i < m; i++)
	{
		int x, y; cin >> x >> y;
		//y pre x
		nodes_that_depend_on[y].push_back(x);
		degree[x]++;
	}

	auto solution = vector<int>(); solution.reserve(n);
	queue<int> removable_nodes;
	for (size_t i = 0; i < degree.size(); i++)
	{
		if (degree[i] == 0)
		{
			removable_nodes.push(i);
		}
	}
	while (!removable_nodes.empty())
	{
		int node_to_remove = removable_nodes.front();
		removable_nodes.pop();
		for (int dependant_node: nodes_that_depend_on[node_to_remove])
		{
			degree[dependant_node]--;
			if (degree[dependant_node] == 0)
				removable_nodes.push(dependant_node);
		}
		solution.push_back(node_to_remove);
	}

	for (int i: solution)
	{
		cout << i << "\n";
	}
	return 0;
}