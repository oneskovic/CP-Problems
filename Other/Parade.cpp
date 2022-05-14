#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int solve(int node, const vector<vector<int>>& tree, vector<vector<int>>& dp, int parent = -1)
{
	int sol = 0;
	for (int neighbor: tree[node])
		if (neighbor != parent)
			sol = max(solve(neighbor, tree, dp, node), sol);
	
	vector<int> neighbor_results; neighbor_results.reserve(tree[node].size());
	for (int neighbor : tree[node])
		if (neighbor != parent)
			neighbor_results.push_back(max(dp[neighbor][0], dp[neighbor][1]));

	sort(neighbor_results.begin(), neighbor_results.end(), greater<int>());
	int deg = tree[node].size();
	dp[node][0] = deg - 1;
	if (neighbor_results.size() >= 1)
		dp[node][1] = neighbor_results[0] + deg - 2;
	if (neighbor_results.size() >= 2)
		dp[node][2] = neighbor_results[0] + neighbor_results[1] + deg - 2;

	int max_of_node = max(dp[node][0], max(dp[node][1] + 1, dp[node][2]));
	return max(sol, max_of_node);
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
	if (n == 2)
	{
		cout << "0\n";
		return 0;
	}
	auto dp = vector<vector<int>>(n, vector<int>(3));
	cout << solve(0, tree, dp);
	return 0;
}