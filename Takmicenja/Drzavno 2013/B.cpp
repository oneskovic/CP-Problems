#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <queue>
using namespace std;
typedef long long ll;

vector<int> bfs(int src, const vector<vector<int>>& graph)
{
	int n = graph.size();

	vector<int> distance_to_node(n, -1);
	distance_to_node[src] = 0;
	queue<pair<int, int>> bfs_queue;
	bfs_queue.push({ src,0 });
	
	while (!bfs_queue.empty())
	{
		int node = bfs_queue.front().first;
		int dist = bfs_queue.front().second;
		bfs_queue.pop();

		for (int neighbor: graph[node])
		{
			if (distance_to_node[neighbor] == -1)
			{
				bfs_queue.push({ neighbor, dist + 1 });
				distance_to_node[neighbor] = dist + 1;
			}
		}
	}
	return distance_to_node;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m, k; cin >> n >> m >> k;
	set<int> banned_nodes;
	for (int i = 0; i < k; i++)
	{
		int node; cin >> node;
		node--;
		banned_nodes.insert(node);
	}
	vector<vector<int>> graph(n, vector<int>());
	for (int i = 0; i < m; i++)
	{
		int a, b; cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	auto distances_from_start = bfs(0, graph);
	int dist_to_end = distances_from_start.back();
	
	vector<vector<int>> graph_no_banned_nodes = vector<vector<int>>(n, vector<int>());
	for (int i = 0; i < n; i++)
	{
		if (banned_nodes.find(i) != banned_nodes.end())
			continue;
		for (int neighbor: graph[i])
		{
			if (banned_nodes.find(neighbor) == banned_nodes.end())
			{
				graph_no_banned_nodes[i].push_back(neighbor);
			}
		}
	}

	auto distances1 = bfs(0, graph_no_banned_nodes);
	auto distances2 = bfs(n - 1, graph_no_banned_nodes);
	vector<int> cnt_distance_in_d1 = vector<int>(n + 1, 0);
	for (int x : distances1)
	{
		if (x != -1)
			cnt_distance_in_d1[x]++;
	}
	ll solution = 0;
	for (int d2: distances2)
	{
		if (d2 >= 0 && dist_to_end - d2 - 1 >= 0)
		{
			solution += cnt_distance_in_d1[dist_to_end - d2 - 1];
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (distances1[i] + distances2[i] + 1 == dist_to_end)
		{
			solution--;
		}
	}
	cout << solution << "\n";

	return 0;
}