#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

ll solution = 0;

vector<ll> solve(int node, const vector<vector<int>>& tree, int k, int parent = -1)
{
	vector<ll> dp(k);
	for (int neighbor: tree[node])
	{
		if (neighbor != parent)
		{
			auto distances = solve(neighbor, tree, k, node);
			for (int i = 0; i <= k - 2; i++)
			{
				int other_dist = k - i - 2;
				solution += (dp[other_dist] * distances[i]);
			}
			solution += distances.back();
			for (int i = 0; i < k; i++)
			{
				dp[i] += distances[i];
			}
		}
	}
	vector<ll> shifted(k);
	copy(dp.begin(), dp.end()-1, shifted.begin() + 1);
	shifted[0] = 1;
	return shifted;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, k; cin >> n >> k;
	vector<vector<int>> tree(n, vector<int>());
	for (int i = 0; i < n-1; i++)
	{
		int a, b; cin >> a >> b;
		a--; b--;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}

	solve(0, tree, k);
	cout << solution << "\n";

	return 0;
}