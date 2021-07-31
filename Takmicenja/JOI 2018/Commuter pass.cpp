#include <algorithm>
#include <limits.h>
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;
typedef long long ll;

vector<vector<int>> shortest_path_dag(const vector<vector<int>>& graph, const vector<vector<int>>& weights, int start_node, int end_node)
{
	int n = graph.size();
	vector<vector<int>> prev_nodes(n);
	vector<ll> length_of_path(n, LLONG_MAX);
	priority_queue<tuple<ll,int, int>, vector<tuple<ll,int,int>>, greater<tuple<ll,int,int>>> nodes_to_visit; 
	nodes_to_visit.push({ 0,-1,start_node });
	while (!nodes_to_visit.empty())
	{
		ll current_path_len = get<0>(nodes_to_visit.top());
		int prev_node = get<1>(nodes_to_visit.top()), current_node = get<2>(nodes_to_visit.top());
		nodes_to_visit.pop();

		if (length_of_path[current_node] > current_path_len)
		{
			length_of_path[current_node] = current_path_len;
			prev_nodes[current_node] = { prev_node };
			for (int i = 0; i < graph[current_node].size(); i++)
			{
				int neighbor = graph[current_node][i];
				ll new_path = current_path_len + weights[current_node][i];
				if (length_of_path[neighbor] >= new_path)
				{
					nodes_to_visit.push({ new_path,current_node,neighbor });
				}
			}
		}
		else if (length_of_path[current_node] == current_path_len)
		{
			prev_nodes[current_node].push_back(prev_node);
		}
	}

	vector<vector<int>> proper_dag(n);
	for (int node = 0; node < n; node++)
	{
		if (node == start_node)
			continue;
		
		for (int prev_node: prev_nodes[node])
		{
			proper_dag[prev_node].push_back(node);
		}
	}

	vector<bool> should_erase(n);
	vector<int> outdegree(n);
	queue<int> q;
	for (int node = 0; node < n; node++)
	{
		outdegree[node] = proper_dag[node].size();
		if (outdegree[node] == 0 && node != end_node)
			q.push(node);
	}
	while (!q.empty())
	{
		int node = q.front();
		should_erase[node] = 1;
		q.pop();
		for (int neighbor: prev_nodes[node])
		{
			outdegree[neighbor]--;
			if (outdegree[neighbor] == 0 && neighbor != end_node)
				q.push(neighbor);
		}
	}

	vector<vector<int>> final_dag(n);
	for (int node = 0; node < n; node++)
	{
		for (int neighbor : proper_dag[node])
		{
			if (!should_erase[neighbor])
				final_dag[node].push_back(neighbor);
		}
	}
	return final_dag;
}

vector<int> topological_sort(const vector<vector<int>>& dag)
{
	int n = dag.size();
	vector<int> in_degree(n);
	for (int i = 0; i < n; i++)
		for (int neighbor: dag[i])
			in_degree[neighbor]++;

	queue<int> nodes_to_visit;
	for (int node = 0; node < n; node++)	
		if (in_degree[node] == 0)
			nodes_to_visit.push(node);
	
	vector<int> sorted_nodes;
	while (!nodes_to_visit.empty())
	{
		int node = nodes_to_visit.front();
		nodes_to_visit.pop();
		sorted_nodes.push_back(node);

		for (int neighbor: dag[node])
		{
			in_degree[neighbor]--;
			if (in_degree[neighbor] == 0)
				nodes_to_visit.push(neighbor);
		}
	}
	return sorted_nodes;
}

vector<ll> dijkstra(const vector<vector<int>>& graph, const vector<vector<int>>& weights, int start_node)
{
	int n = graph.size();
	vector<ll> length_of_path(n, LLONG_MAX/2);
	priority_queue<pair<ll, int>, vector<pair<ll,int>>, greater<pair<ll,int>>> nodes_to_visit;
	nodes_to_visit.push({ 0,start_node });
	while (!nodes_to_visit.empty())
	{
		ll current_dist = nodes_to_visit.top().first;
		int current_node = nodes_to_visit.top().second;
		nodes_to_visit.pop();
		if (current_dist < length_of_path[current_node])
		{
			for (int i = 0; i < graph[current_node].size(); i++)
			{
				int neighbor = graph[current_node][i];
				ll new_dist = current_dist + weights[current_node][i];
				if (length_of_path[neighbor] > new_dist)
				{
					nodes_to_visit.push({ new_dist, neighbor });
				}
			}
			length_of_path[current_node] = current_dist;
		}
	}
	return length_of_path;
}

ll solve(const vector<vector<int>>& graph, const vector<vector<int>>& weights, int start_node, int end_node, int node_u, int node_v)
{
	auto dag = shortest_path_dag(graph, weights, start_node, end_node);
	auto distance_from_u = dijkstra(graph, weights, node_u);
	ll solution = distance_from_u[node_v];
	// Edges are bidirectional so it suffices to call dijkstra for v on the normal graph
	// if they were not, the graph would have to be transposed
	auto distance_from_v = dijkstra(graph, weights, node_v);
	auto top_sort = topological_sort(dag);
	vector<bool> visited(graph.size());
	for (int node: top_sort)
	{
		ll current_dist_u = distance_from_u[node];
		ll current_dist_v = distance_from_v[node];
		for (int child: dag[node])
		{
			if (!visited[child])
			{
				distance_from_u[child] = min(distance_from_u[child], current_dist_u);;
				distance_from_v[child] = min(distance_from_v[child], current_dist_v);
			}
			if (distance_from_u[child] + distance_from_v[child] > current_dist_v + current_dist_u)
			{
				distance_from_u[child] = min(distance_from_u[child], current_dist_u);
				distance_from_v[child] = min(distance_from_v[child], current_dist_v);
			}
			visited[child] = 1;
		}
	}
	for (int node = 0; node < graph.size(); node++)
		if (distance_from_u[node] < LLONG_MAX && distance_from_v[node] < LLONG_MAX)
			solution = min(solution, distance_from_u[node] + distance_from_v[node]);
	return solution;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int node_cnt, edge_cnt; cin >> node_cnt >> edge_cnt;
	int start_node, end_node, node_u, node_v;
	cin >> start_node >> end_node >> node_u >> node_v;
	start_node--, end_node--, node_u--, node_v--;
	vector<vector<int>> graph(node_cnt), weights(node_cnt);
	for (int i = 0; i < edge_cnt; i++)
	{
		int a, b, w;
		cin >> a >> b >> w;
		a--; b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
		weights[a].push_back(w);
		weights[b].push_back(w);
	}
	ll sol1 = solve(graph, weights, start_node, end_node, node_u, node_v);
	ll sol2 = solve(graph, weights, start_node, end_node, node_v, node_u);
	cout << min(sol1, sol2);

	return 0;
}