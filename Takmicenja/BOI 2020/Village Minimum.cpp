#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
typedef long long ll;

void solve(int node, const vector<vector<int>>& tree, vector<vector<int>>& unmoved_neighbors, vector<int>& values, int parent = -1)
{
	for (int neighbor: tree[node])
	{
		if (neighbor != parent)
		{
			solve(neighbor, tree, unmoved_neighbors, values, node);
		}
	}
	if (values[node] == node) // Node is not moved
	{

	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<vector<int>> tree(n, vector<int>());
	vector<int> values(n);
	iota(values.begin(), values.end(), 0);
	for (int i = 0; i < n-1; i++)
	{
		int a, b; cin >> a >> b;
		a--; b--;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}
	auto unmoved_neighbors = tree;

	return 0;
}