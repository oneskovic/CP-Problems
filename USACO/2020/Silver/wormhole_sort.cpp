#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <set>
using namespace std;

void dfs(int node, int component_id, const vector<set<int>>& graph, vector<int>& component)
{
	component[node] = component_id;
	for (int neighbor: graph[node])
	{
		if (component[neighbor] == -1)
		{
			dfs(neighbor, component_id, graph, component);
		}
	}
}

bool check(int value_to_check, vector<set<int>> graph, const vector<vector<int>>& edges, const vector<pair<int,int>>& to_swap)
{
	for (auto e: edges)
	{
		if (e[2] < value_to_check)
		{
			graph[e[0]].erase(e[1]);
			graph[e[1]].erase(e[0]);
		}
	}

	vector<int> component(graph.size(), -1);
	for (int i = 1; i < graph.size(); i++)
	{
		if (component[i] == -1)
		{
			dfs(i, i, graph, component);
		}
	}

	for (auto p: to_swap)
	{
		int node1 = p.first;
		int node2 = p.second;
		if (component[node1] != component[node2])
		{
			return false;
		}
	}
	return true;
}

int main()
{
	freopen("wormsort.in", "r", stdin);
	freopen("wormsort.out", "w", stdout);
	
	int node_count, edge_count;
	cin >> node_count >> edge_count;
	vector<int> numbers(node_count+1);
	for (int i = 1; i <= node_count; i++)
	{
		cin >> numbers[i];
	}

	vector<pair<int, int>> to_swap;
	for (int i = 1; i <= node_count; i++)
	{
		if (numbers[i] != i)
		{
			to_swap.emplace_back(numbers[i], numbers[numbers[i]]);
		}
	}

	vector<set<int>> graph (node_count+1);
	vector<vector<int>> edges;
	vector<int> weights;
	for (size_t i = 0; i < edge_count; i++)
	{
		int node1, node2, weight;
		cin >> node1 >> node2 >> weight;
		weights.push_back(weight);
		graph[node1].insert(node2);
		graph[node2].insert(node1);
		edges.push_back({ node1, node2, weight });
	}

	if (to_swap.empty())
	{
		cout << -1;
		return 0;
	}

	sort(weights.begin(), weights.end());
	weights.erase(unique(weights.begin(), weights.end()), weights.end());

	int l = 0;
	int r = weights.size();
	while (l+1 < r)
	{
		int mid = (l + r) / 2;
		int value_to_check = weights[mid];
		if (check(value_to_check, graph, edges, to_swap))
			l = mid;
		else
			r = mid;
	}
	cout << weights[l];
	return 0;
}