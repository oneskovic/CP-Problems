#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int find_cycle(int node, const vector<int>& dest, vector<bool>& visited, vector<int>& sol)
{
	visited[node] = 1;

	if (sol[dest[node]] != -1)
		sol[node] = sol[dest[node]] + 1;

	if (visited[dest[node]])
		return dest[node];

	int x = find_cycle(dest[node], dest, visited, sol);

	if (sol[dest[node]] != -1)
		sol[node] = sol[dest[node]] + 1;

	return x;
}

int fill_cycle(int node, const vector<int>& dest, vector<int>& sol, vector<bool>& visited, int current_len = 0)
{
	if (visited[node])
		return current_len;
	
	visited[node] = 1;
	sol[node] = fill_cycle(dest[node], dest, sol, visited, current_len + 1);
	return sol[node];
}

void dfs(int node,const vector<int>& dest, vector<int>& sol)
{
	if (sol[dest[node]] == -1)
		dfs(dest[node], dest, sol);
	sol[node] = sol[dest[node]] + 1;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<int> dest(n);
	vector<int> sol(n, -1);
	for (int i = 0; i < n; i++)
	{
		int x; cin >> x;
		dest[i] = x - 1;
	}

	vector<bool> found_component(n);
	vector<bool> visited(n);
	for (int i = 0; i < n; i++)
	{
		if (!found_component[i])
		{
			int x = find_cycle(i, dest, found_component, sol);
			if (sol[i] == -1)
			{
				fill_cycle(x, dest, sol, visited);
				if (sol[i] == -1)
					dfs(i, dest, sol);
			}
		}
	}
	for (int i: sol)
		cout << i << " ";
	

	return 0;
}