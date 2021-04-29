#include <algorithm>
#include <limits.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int node_cnt, edge_cnt; cin >> node_cnt >> edge_cnt;
	vector<vector<int>> neighbors(node_cnt, vector<int>());
	vector<vector<double>> weights(node_cnt, vector<double>());

	for (size_t i = 0; i < edge_cnt; i++)
	{
		int a, b;
		double w;
		cin >> a >> b >> w;
		neighbors[a].push_back(b);
		weights[a].push_back(w);
	}

	priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> min_heap;
	vector<double> dp(node_cnt, numeric_limits<double>::infinity());
	vector<bool> done(node_cnt, 0);
	vector<int> prev_node(node_cnt, -1);

	int start_node, end_node; cin >> start_node >> end_node;
	min_heap.emplace(0, start_node);
	dp[start_node] = 0;
	while (!min_heap.empty())
	{
		double current_path = min_heap.top().first;
		int current_node = min_heap.top().second;

		if (current_node == end_node)
			break;

		min_heap.pop();
		if (done[current_node])
			continue;
		done[current_node] = 1;
		
		for (int i = 0; i < neighbors[current_node].size(); i++)
		{
			int neighbor = neighbors[current_node][i];
			double w = weights[current_node][i];
			if (!done[neighbor] && dp[neighbor] > current_path + w)
			{
				prev_node[neighbor] = current_node;
				dp[neighbor] = current_path + w;
				min_heap.emplace(dp[neighbor], neighbor);
			}
		}
	}

	if (dp[end_node] == numeric_limits<double>::infinity())
	{
		cout << "ne\n";
		return 0;
	}
	
	cout << setprecision(5) << fixed << dp[end_node] << "\n";
	vector<int> path = {};
	int node = end_node;
	while (node != -1)
	{
		path.push_back(node);
		node = prev_node[node];
	}
	reverse(path.begin(), path.end());
	for (int i : path)
		cout << i << " ";

	return 0;
}