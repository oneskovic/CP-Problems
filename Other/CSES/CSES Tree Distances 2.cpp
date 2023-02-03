#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
typedef long long ll;

void get_subtree_size(int node, int parent, const vector<vector<int>>& tree, vector<int>& subtree_size)
{
	subtree_size[node] = 1;
	for (int neighbor: tree[node])
	{
		if (neighbor != parent)
		{
			get_subtree_size(neighbor, node, tree, subtree_size);
			subtree_size[node] += subtree_size[neighbor];
		}
	}
}

void dfs(int node, const vector<vector<int>>& tree, vector<ll>& dist, int current_dist = 0)
{
	dist[node] = current_dist;
	for (int neighbor : tree[node])
		if (dist[neighbor] == -1)
			dfs(neighbor, tree, dist, current_dist + 1);
}

void dfs_dist_sum(int node, int parent, const vector<vector<int>>& tree, const vector<int>& subtree_size, vector<ll>& dist_sum)
{
	int n = tree.size();
	for (int neighbor: tree[node])
	{
		if (neighbor != parent)
		{
			dist_sum[neighbor] = dist_sum[node] + n - 2 * subtree_size[neighbor];
			dfs_dist_sum(neighbor, node, tree, subtree_size, dist_sum);
		}
	}
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
	vector<int> subtree_size(n);
	get_subtree_size(0, -1, tree, subtree_size);
	vector<ll> distances(n, -1);
	dfs(0, tree, distances);
	ll dist_sum_root = accumulate(distances.begin(), distances.end(), (ll)0);
	vector<ll> dist_sums(n);
	dist_sums[0] = dist_sum_root;
	dfs_dist_sum(0, -1, tree, subtree_size, dist_sums);
	for (ll x: dist_sums)
		cout << x << " ";
	

	return 0;
}