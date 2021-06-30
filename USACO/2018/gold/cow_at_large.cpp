#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
	freopen("atlarge.in", "r", stdin);
	freopen("atlarge.out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, start_vertex; cin >> n >> start_vertex;
	vector<vector<int>> tree(n+1, vector<int>());
	for (int i = 0; i < n-1; i++)
	{
		int a, b; cin >> a >> b;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}
	
	queue<pair<int, int>> bfs_queue;
	vector<int> color(n + 1, -1);

	for (int i = 1; i <= n; i++)
	{
		if (tree[i].size() == 1) {
			bfs_queue.push({ 0,i });
			color[i] = 0;
			if (i == start_vertex)
			{
				return 1;
			}
		}

	}
	bfs_queue.push({ 1,start_vertex });
	color[start_vertex] = 1;

	while (!bfs_queue.empty())
	{
		int current_color = bfs_queue.front().first;
		int current_node = bfs_queue.front().second;
		bfs_queue.pop();
		for (int neighbor : tree[current_node])
		{
			if (color[neighbor] == -1)
			{
				color[neighbor] = current_color;
				bfs_queue.push({ current_color, neighbor });
			}
		}
	}

	int solution = 0;
	for (int node = 1; node <= n; node++)
	{
		for (int neighbor : tree[node])
		{
			if (color[node] != color[neighbor] && node < neighbor)
			{
				solution++;
			}
		}
	}
	cout << solution;
	return 0;
}