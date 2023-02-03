#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

struct point
{
	int x, y, power;
};

bool are_connected(point transmiter, point reciever)
{
	int dx = transmiter.x - reciever.x;
	int dy = transmiter.y - reciever.y;
	return dx * dx + dy * dy <= transmiter.power * transmiter.power;
}

int count_reachable_nodes(int node, vector<bool>& visited, const vector<vector<int>>& graph)
{
	int res = 1;
	visited[node] = 1;
	for (int neighbor: graph[node])
		if (!visited[neighbor])
			res += count_reachable_nodes(neighbor, visited, graph);	
	return res;
}

int main()
{
	freopen("moocast.in", "r", stdin);
	freopen("moocast.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<vector<int>> graph(n, vector<int>());
	vector<point> points(n);
	for (int i = 0; i < n; i++)
		cin >> points[i].x >> points[i].y >> points[i].power;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				continue;
			if (are_connected(points[i],points[j]))
				graph[i].push_back(j);
		}
	}

	int max_reachable_nodes = 0;
	for (int start_node = 0; start_node < n; start_node++)
	{
		vector<bool> visited(n);
		max_reachable_nodes = max(max_reachable_nodes, count_reachable_nodes(start_node, visited, graph));
	}
	cout << max_reachable_nodes;

	return 0;
}