#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <chrono>
using namespace std;
typedef long long ll;

bool dfs(int node, vector<vector<int>>& graph, vector<bool>& visited, int visited_cnt)
{
	if (visited_cnt == visited.size()-2)
	{
		return true;
	}
	visited[node] = 1;
	bool possible = false;
	for (int neighbor: graph[node])
	{
		if (!visited[neighbor])
		{
			if (dfs(neighbor, graph, visited, visited_cnt + 1))
				possible = true;
		}
	}
	visited[node] = 0;
	return possible;
}

bool brutus(int n, vector<bool> directions)
{
	vector<vector<int>> graph(n+2, vector<int>());
	for (int i = 1; i <= n-1; i++)
	{
		graph[i].push_back(i + 1);
	}
	for (int i = 0; i < n; i++)
	{
		if (directions[i] == 0)
		{
			graph[i + 1].push_back(n + 1);
		}
		else
		{
			graph[n + 1].push_back(i);
		}
	}

	for (int i = 0; i < graph.size(); i++)
	{
		vector<bool> visited(graph.size(), 0);
		if (dfs(i,graph,visited,0))
		{
			return true;
		}
	}
	return false;
}

vector<bool> rand_vec(int n)
{
	vector<bool> v(n);
	for (int i = 0; i < n; i++)
	{
		v[i] = rand() % 2;
	}
	return v;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	srand(time(0));

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<bool> directions(n);
		for (int i = 0; i < n; i++)
		{
			int a; cin >> a;
			directions[i] = a;
		}
		
		vector<int> solution = { -1 };
		for (int i = 0; i < n-1; i++)
		{
			if (directions[i] != directions[i + 1])
			{
				solution = vector<int>(n);
				iota(solution.begin(), solution.end(), 1);
				solution.insert(solution.begin()+i+1, n + 1);
				break;
			}
		}
		if (directions[0] == 1)
		{
			solution = vector<int>(n + 1);
			iota(solution.begin() + 1, solution.end(), 1);
			solution[0] = n + 1;
		}
		if (directions.back() == 0)
		{
			solution = vector<int>(n + 1);
			iota(solution.begin(), solution.end(), 1);
		}
		
		

		for (int i : solution)
		{
			cout << i << " ";
		}
		cout << "\n";

	}
	return 0;
}