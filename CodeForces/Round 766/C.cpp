#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;
typedef long long ll;

vector<int> generate_primes(int n)
{
	vector<int> sieve(n, 1);
	sieve[0] = 0;
	sieve[1] = 0;
	vector<int> primes; primes.reserve(10000);
	for (int i = 2; i < sieve.size(); i++)
	{
		if (sieve[i])
		{
			primes.push_back(i);
			for (int j = 2 * i; j < sieve.size(); j += i)
			{
				sieve[j] = 0;
			}
		}
	}
	return primes;
}

void dfs(int node, int prev_node, int prev_assignment, const vector<vector<int>>& tree, map<pair<int,int>,int>& assignments)
{
	int assignment = 0;
	if (prev_assignment == 2)
	{
		assignment = 11;
	}
	else
	{
		assignment = 2;
	}
	pair<int, int> p = { min(prev_node,node),max(prev_node,node) };
	assignments[p] = assignment;
	for (int i: tree[node])
	{
		if (i != prev_node)
		{
			dfs(i, node, assignment, tree, assignments);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;

	while (test_cnt--)
	{
		int n; cin >> n;
		vector<vector<int>> tree(n, vector<int>());
		vector<pair<int, int>> edges; edges.reserve(n - 1);
		vector<int> degree(n);
		for (int i = 0; i < n-1; i++)
		{
			int u, v; cin >> u >> v;
			u--; v--;
			tree[u].push_back(v);
			tree[v].push_back(u);
			degree[u]++;
			degree[v]++;
			edges.emplace_back(min(u, v), max(u, v));
		}
		bool possible = 1;
		int leaf_node = -1;
		for (int i = 0; i < n; i++)
		{
			if (degree[i] > 2)
			{
				cout << "-1\n";
				possible = 0;
				break;
			}
			if (degree[i] == 1)
			{
				leaf_node = i;
			}
		}
		if (possible)
		{
			map<pair<int, int>, int> assignments;
			dfs(leaf_node, -1, 2,tree, assignments);
			for (auto edge: edges)
			{
				cout << assignments[edge] << " ";
			}
		}
	}

	return 0;
}