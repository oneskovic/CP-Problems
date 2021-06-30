#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> query_distances(int node, int n)
{
	cout << "? " <<  node << endl;
	vector<int> distances(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> distances[i];
	return distances;
}
vector<int> query_neighbors(int node, int n)
{
	auto distances = query_distances(node, n);
	vector<int> neighbors;
	for (int i = 1; i <= n; i++)
	{
		if (distances[i] == 1)
		{
			neighbors.push_back(i);
		}
	}
	return neighbors;
}

int main()
{
	int n; cin >> n;
	vector<int> color(n + 1);
	auto distances = query_distances(1, n);
	vector<int> nodes_color_0, nodes_color_1;
	for (int i = 2; i <= n; i++)
	{
		if (distances[i] % 2 == 1)
		{
			nodes_color_0.push_back(i);
		}
		else
		{
			nodes_color_1.push_back(i);
		}
	}
	vector<pair<int, int>> edges; edges.reserve(n - 1);
	if (nodes_color_1.size() <= nodes_color_0.size())
	{
		for (int i = 1; i <= n; i++)
		{
			if (distances[i] == 1)
			{
				edges.emplace_back(1, i);
			}
		}
	}

	vector<int>& nodes_to_query = nodes_color_0.size() < nodes_color_1.size() ? nodes_color_0 : nodes_color_1;
	for (int node: nodes_to_query)
	{
		auto neighbors = query_neighbors(node, n);
		for (int neighbor: neighbors)
		{
			edges.emplace_back(node, neighbor);
		}
	}
	cout << "!" << endl;
	for (auto edge: edges)
	{
		cout << edge.first << " " << edge.second << endl;
	}
	
	return 0;
}