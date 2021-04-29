#include <functional>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <vector>
#include <tuple>
#include <queue>
using namespace std;
typedef priority_queue<tuple<double, int, int>, vector<tuple<double, int, int>>, greater<tuple<double, int, int>>> min_heap;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int node_cnt, edge_cnt;
	cin >> node_cnt >> edge_cnt;
	vector<vector<int>> neighbors(node_cnt, vector<int>());
	vector<vector<double>> weights(node_cnt, vector<double>());

	int current_node = -1;
	for (int i = 0; i < edge_cnt; i++)
	{
		int a, b;
		double w;
		cin >> a >> b >> w;
		neighbors[a].push_back(b);
		neighbors[b].push_back(a);
		weights[a].push_back(w);
		weights[b].push_back(w);
		current_node = a;
	}

	min_heap current_edges;
	vector<bool> is_in_tree(node_cnt, 0);
	int taken_edges = 0;
	double total_weight = 0;
	while (taken_edges < node_cnt-1)
	{
		is_in_tree[current_node] = 1;
		for (int i = 0; i < neighbors[current_node].size(); i++)
		{
			int neighbor = neighbors[current_node][i];
			double weight = weights[current_node][i];
			current_edges.push({ weight,current_node,neighbor });
		}
		
		auto min_edge = current_edges.top();
		int outside_node = get<2>(min_edge);
		current_edges.pop();
		while (is_in_tree[outside_node])
		{
			min_edge = current_edges.top();
			outside_node = get<2>(min_edge);
			current_edges.pop();
		}
		taken_edges++;
		total_weight += get<0>(min_edge);
		current_node = outside_node;
	}
	cout << setprecision(1) << fixed << total_weight;

	return 0;
}
