#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;

vector<int> get_neighbors(int row, int col, const vector<bool>& is_dist_valid)
{
	int n = 51;
	vector<int> neighbors;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int dist = (i - row) * (i - row) + (j - col) * (j - col);
			if (is_dist_valid[dist])
			{
				neighbors.push_back(i * n + j);
			}
		}
	}
	return neighbors;
}

vector<vector<int>> build_graph()
{
	int n = 51;
	vector<vector<int>> graph(n * n, vector<int>());
	vector<bool> is_dist_valid(2*n * n+1);

	for (int i = 0; i * i < is_dist_valid.size(); i++)
		is_dist_valid[i * i] = 1;
		
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)	
			graph[i*n+j] = get_neighbors(i, j, is_dist_valid);
			
	return graph;
}

vector<int> bfs(int node, const vector<vector<int>>& graph)
{
	queue<pair<int, int>> bfs_queue;
	bfs_queue.push({ node,0 });
	int n = graph.size();
	vector<int> dist(n, -1);
	dist[node] = 0;
	while (!bfs_queue.empty())
	{
		int node = bfs_queue.front().first;
		int current_dist = bfs_queue.front().second;
		bfs_queue.pop();
		for (int neighbor: graph[node])
		{
			if (dist[neighbor] == -1)
			{
				dist[neighbor] = current_dist + 1;
				bfs_queue.push({ neighbor, current_dist + 1 });
			}
		}
	}
	return dist;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_cnt; cin >> test_cnt;

	auto graph = build_graph();
	auto distances = bfs(0, graph);

	int n = 51;
	while (test_cnt--)
	{

		int row, col; cin >> row >> col;
		cout << distances[row*n+col] << "\n";
	}
	return 0;
}