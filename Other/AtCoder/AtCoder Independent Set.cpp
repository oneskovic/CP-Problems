#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;

pair<ll,ll> solve(int node, const vector<vector<int>>& tree, int parent = -1)
{
	ll color_black = 1;
	ll color_white = 1;
	for (int neighbor: tree[node])
	{
		if (neighbor != parent)
		{
			auto s = solve(neighbor, tree, node);
			ll s_black = s.first;
			ll s_white = s.second;
			color_black *= s_white;
			color_white *= (s_white + s_black);
			color_black %= mod;
			color_white %= mod;
		}
	}
	return {color_black, color_white};
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<vector<int>> tree(n, vector<int>());	
	for (int i = 0; i < n - 1; i++)
	{
		int a, b; cin >> a >> b;
		a--; b--;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}
	auto sol = solve(0, tree);
	cout << (sol.first + sol.second)%mod << "\n";

	return 0;
}