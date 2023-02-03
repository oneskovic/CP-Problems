#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

void dfs(int node, int component_id, const vector<vector<int>>& graph, vector<int>& node_component, vector<int>& edge_cnt)
{
	node_component[node] = component_id;
	for (int neighbor: graph[node])
	{
		if (neighbor > node)
			edge_cnt[component_id]++;
		
		if (node_component[neighbor] == -1)
		{
			dfs(neighbor, component_id, graph, node_component, edge_cnt);
		}
	}
}

ll binpow(ll x, ll pow)
{
	if (pow == 1)
		return x;
	ll res = binpow(x, pow / 2);
	if (pow % 2 == 0)
		return (res * res) % mod;
	else
		return ((res * res) % mod) * x % mod;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<vector<int>> graph(n, vector<int>());
		for (int i = 0; i < n; i++)
		{
			int a, b; cin >> a >> b;
			a--; b--;
			graph[a].push_back(b); graph[b].push_back(a);
		}
		vector<int> node_component(n,-1);
		vector<int> edge_cnt;
		vector<int> node_cnt;
		int component_id = 0;
		for (int i = 0; i < n; i++)
		{
			if (node_component[i] == -1)
			{
				edge_cnt.push_back(0);
				node_cnt.push_back(0);
				dfs(i, component_id++, graph, node_component, edge_cnt);
			}
			node_cnt[node_component[i]] += 1;
		}

		bool possible = 1;
		for (int component = 0; component < component_id; component++)
		{
			if (edge_cnt[component] < node_cnt[component])
				possible = 0;
		}
		if (possible)
			cout << binpow(2, component_id) << "\n";
		else
			cout << "0\n";
	}

	return 0;
}