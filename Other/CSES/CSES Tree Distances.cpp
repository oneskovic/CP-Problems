#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

void dfs(int node, const vector<vector<int>>& tree, vector<int>& dist, int current_dist = 0)
{
	dist[node] = current_dist;
	for (int neighbor : tree[node])
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
	vector<int> dist1(n, -1);
	dfs(0, tree, dist1);
	int node1 = max_element(dist1.begin(), dist1.end()) - dist1.begin();
	dist1 = vector<int>(n, -1);
	dfs(node1, tree, dist1);
	auto dist2 = vector<int>(n, -1);
	int node2 = max_element(dist1.begin(), dist1.end()) - dist1.begin();
	dfs(node2, tree, dist2);

	for (int i = 0; i < n; i++)
	{
		cout << max(dist1[i], dist2[i]) << " ";
	}
	
	return 0;
}