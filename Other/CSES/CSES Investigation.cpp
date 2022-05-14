#include <algorithm>
#include <iostream>
#include <limits.h>
#include <vector>
#include <tuple>
#include <queue>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

pair<ll,vector<vector<int>>> shortest_path_dag(const vector<vector<int>>& graph, const vector<vector<int>>& weights)
{
	int n = graph.size();
	priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int>>, greater<tuple<ll, int, int>>> pq;
	vector<ll> distance_to_node(n, LLONG_MAX);
	vector<vector<int>> nodes_on_shortest_path(n);
	int source = 0;
	pq.push({ 0,source, -1 });
	
	while (!pq.empty())
	{
		ll current_distance = get<0>(pq.top());
		int current_node = get<1>(pq.top());
		int previous_node = get<2>(pq.top());
		pq.pop();

		if (current_distance < distance_to_node[current_node])
		{
			distance_to_node[current_node] = current_distance;
			nodes_on_shortest_path[current_node] = { previous_node };
			for (int i = 0; i < graph[current_node].size(); i++)
			{
				int neighbor = graph[current_node][i];
				if (current_distance + weights[current_node][i] < distance_to_node[neighbor])
				{
					pq.push({ current_distance + weights[current_node][i], neighbor, current_node });
				}
			}
		}
		else if (current_distance == distance_to_node[current_node])
		{
			nodes_on_shortest_path[current_node].push_back(previous_node);
		}
	}

	vector<vector<int>> proper_dag(n);
	for (int node = 1; node < n; node++)
	{
		for (int prev_node: nodes_on_shortest_path[node])
		{
			proper_dag[prev_node].push_back(node);
		}
	}
	return { distance_to_node.back(),proper_dag };
}

int shortest_path_in_dag(const vector<vector<int>>& dag, int end_node)
{
	int n = dag.size();
	queue<pair<int, int>> bfs_queue;
	vector<bool> visited(n);
	bfs_queue.push({ 0,0 });
	while (!bfs_queue.empty())
	{
		int node = bfs_queue.front().first, dist = bfs_queue.front().second;
		bfs_queue.pop();
		visited[node] = 1;
		if (node == end_node)
			return dist;
		for (int neighbor: dag[node])
		{
			if (!visited[neighbor])
			{
				visited[neighbor] = 1;
				bfs_queue.push({ neighbor, dist + 1 });
			}
		}
	}
	return INT_MAX;
}

int longest_path_in_dag(const vector<vector<int>>& dag, int end_node)
{
	int n = dag.size();

	vector<int> in_degree(n);
	for (int node = 0; node < dag.size(); node++)
	{
		for (int neighbor : dag[node])
		{
			in_degree[neighbor]++;
		}
	}

	queue<pair<int, int>> bfs_queue;
	bfs_queue.push({ 0,0 });
	while (!bfs_queue.empty())
	{
		int node = bfs_queue.front().first, dist = bfs_queue.front().second;
		if (node == end_node)
		{
			return dist;
		}
		bfs_queue.pop();
		for (int neighbor : dag[node])
		{
			in_degree[neighbor]--;
			if (in_degree[neighbor] == 0)
			{
				bfs_queue.push({ neighbor, dist + 1 });
			}
		}
	}
	return INT_MAX;
}

ll count_paths_in_dag(const vector<vector<int>>& dag, int end_node)
{
	int n = dag.size();

	vector<int> in_degree(n);
	for (int node = 0; node < dag.size(); node++)
		for (int neighbor : dag[node])
			in_degree[neighbor]++;

	queue<int> bfs_queue;
	vector<ll> path_count(n);
	path_count[0] = 1;
	bfs_queue.push(0);
	while (!bfs_queue.empty())
	{
		int node = bfs_queue.front();
		path_count[node] %= mod;
		if (node == end_node)
		{
			return path_count[node];
		}
		bfs_queue.pop();
		for (int neighbor : dag[node])
		{
			path_count[neighbor] += path_count[node];
			in_degree[neighbor]--;
			if (in_degree[neighbor] == 0)
			{
				bfs_queue.push(neighbor);
			}
		}
	}
	return INT_MAX;
}

int main()
{
	//freopen("test_input.txt", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int node_cnt, edge_cnt;
	cin >> node_cnt >> edge_cnt;
	vector<vector<int>> graph(node_cnt), weights(node_cnt);
	for (int i = 0; i < edge_cnt; i++)
	{
		int a, b, weight;
		cin >> a >> b >> weight;
		a--; b--;
		graph[a].push_back(b);
		weights[a].push_back(weight);
	}
	auto temp = shortest_path_dag(graph, weights);
	auto& dag = temp.second;
	cout << temp.first << " " << count_paths_in_dag(dag, node_cnt - 1) << " "
		<< shortest_path_in_dag(dag, node_cnt-1) << " " << longest_path_in_dag(dag, node_cnt - 1);
	return 0;
}