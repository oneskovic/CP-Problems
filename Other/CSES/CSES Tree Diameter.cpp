#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

void dfs(int node, const vector<vector<int>>& tree, vector<int>& dist, int current_dist = 0)
{
	dist[node] = current_dist;
	for (int neighbor: tree[node])
		if (dist[neighbor] == -1)
			dfs(neighbor, tree, dist, current_dist + 1);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<vector<int>> tree(n, vector<int>());
	for (int i = 0; i < n-1; i++)
	{
		int a, b; cin >> a >> b;
		a--; b--;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}
	vector<int> dist(n, -1);
	dfs(0, tree, dist);
	auto it = max_element(dist.begin(), dist.end());
	int max_dist_node = it - dist.begin();
	dist = vector<int>(n, -1);
	dfs(max_dist_node, tree, dist);
	cout << *max_element(dist.begin(), dist.end());

	return 0;
}