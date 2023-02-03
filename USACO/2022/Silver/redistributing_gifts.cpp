#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

void dfs(int node, vector<bool>& visited, const vector<vector<int>>& graph)
{
	visited[node] = 1;
	for (int neighbor : graph[node])
	{
		if (!visited[neighbor])
			dfs(neighbor, visited, graph);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<vector<int>> preferences(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> preferences[i][j]; preferences[i][j]--;
		}
		reverse(preferences[i].begin(), preferences[i].end());
	}
	vector<vector<int>> graph(n, vector<int>());
	for (int node = 0; node < n; node++)
	{
		auto it = find(preferences[node].begin(), preferences[node].end(), node);
		while (it != preferences[node].end())
		{
			graph[node].push_back(*it);
			it++;
		}
	}

	vector<vector<bool>> is_reachable(n, vector<bool>(n));
	for (int i = 0; i < n; i++)
		dfs(i, is_reachable[i], graph);
	
	for (int node = 0; node < n; node++)
	{
		int sol = node;
		for (int pref: preferences[node])
			if (is_reachable[node][pref] && is_reachable[pref][node])
				sol = pref;
		cout << sol+1 << "\n";
	}
	
	return 0;
}