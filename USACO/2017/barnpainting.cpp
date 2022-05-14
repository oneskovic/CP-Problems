#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;

ll sum_not_equal(int color, const vector<ll>& res)
{
	ll sol = 0;
	for (int i = 0; i < res.size(); i++)
	{
		if (i != color)
			sol += res[i];
	}
	return sol;
}

vector<ll> solve(int node, const vector<vector<int>>& tree, const vector<int>& painted, int parent = -1)
{
	vector<ll> solutions = { 1,1,1 };
	if (painted[node] != -1)
	{
		int c = painted[node];
		solutions = { 0,0,0 };
		solutions[c] = 1;
	}
	for (int neighbor : tree[node])
	{
		if (neighbor != parent)
		{
			auto sol = solve(neighbor, tree, painted, node);
			for (int i = 0; i < solutions.size(); i++)
			{
				solutions[i] *= sum_not_equal(i, sol);
				solutions[i] %= mod;
			}
		}
	}
	return solutions;
}

int main()
{
	freopen("barnpainting.in", "r", stdin);
	freopen("barnpainting.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, k; cin >> n >> k;
	vector<vector<int>> tree(n, vector<int>());
	for (int i = 0; i < n - 1; i++)
	{
		int a, b; cin >> a >> b;
		a--; b--;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}
	vector<int> colored(n,-1);
	for (int i = 0; i < k; i++)
	{
		int node, c; 
		cin >> node >> c;
		c--;
		node--;
		colored[node] = c;
	}
	auto sol = solve(0, tree, colored);
	cout << (sol[0]+sol[1]+sol[2]) % mod;

	return 0;
}