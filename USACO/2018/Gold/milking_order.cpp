#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> topological_sort(const vector<vector<int>>& graph)
{
	int n = graph.size();
	priority_queue<int,vector<int>,greater<int>> pq;
	vector<int> in_degree(n);
	for (int i = 0; i < graph.size(); i++)
		for (int neighbor: graph[i])
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
		for (int neighbor: graph[node])
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

vector<vector<int>> build_graph(const vector<vector<int>>& queries, int node_cnt, int to_check)
{
	vector<vector<int>> graph(node_cnt);
	for (int i = 0; i < to_check; i++)
	{
		for (int j = 1; j < queries[i].size(); j++)
		{
			int prev_node = queries[i][j - 1];
			int current_node = queries[i][j];
			graph[prev_node].push_back(current_node);
		}
	}
	return graph;
}

bool check(const vector<vector<int>>& graph)
{
	int n = graph.size();
	return topological_sort(graph).size() == n;
}

int main()
{
	freopen("milkorder.in", "r", stdin);
	freopen("milkorder.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, query_cnt; cin >> n >> query_cnt;
	vector<vector<int>> queries(query_cnt);
	for (int i = 0; i < query_cnt; i++)
	{
		int nodes_in_query; cin >> nodes_in_query;
		vector<int> query(nodes_in_query);
		for (int j = 0; j < nodes_in_query; j++)
		{
			cin >> query[j];
			query[j]--;
		}
		queries[i] = query;
	}

	int l = 0, r = query_cnt + 1;
	while (r - l > 1)
	{
		int mid = (l + r) / 2;
		auto graph = build_graph(queries, n, mid);
		if (check(graph))
			l = mid;
		else
			r = mid;
	}
	auto graph = build_graph(queries, n, l);
	auto solution = topological_sort(graph);
	for (int i = 0; i < n - 1; i++)
		cout << solution[i]+1 << " ";
	cout << solution.back()+1;

	return 0;
}