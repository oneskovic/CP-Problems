#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> topological_sort(const vector<vector<int>>& graph)
{
	int n = graph.size();
	priority_queue<int, vector<int>, greater<int>> pq;
	vector<int> in_degree(n);
	for (int i = 0; i < graph.size(); i++)
		for (int neighbor : graph[i])
			in_degree[neighbor]++;

	for (int i = 0; i < n; i++)
		if (in_degree[i] == 0)
			pq.push(i);

	vector<int> sorted_nodes; sorted_nodes.reserve(n);
	while (!pq.empty())
	{
		int node = pq.top();
		pq.pop();
		sorted_nodes.push_back(node);
		for (int neighbor : graph[node])
		{
			in_degree[neighbor]--;
			if (in_degree[neighbor] == 0)
			{
				pq.push(neighbor);
			}
		}
	}
	return sorted_nodes;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int node_cnt, edge_cnt;
	cin >> node_cnt >> edge_cnt;
	vector<vector<int>> graph(node_cnt);
	for (int i = 0; i < edge_cnt; i++)
	{
		int a, b; cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
	}
	auto solution = topological_sort(graph);
	for (int i : solution)
		cout << i+1 << " ";
	return 0;
}