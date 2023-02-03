#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;

void dfs(int node, int parent, const vector<vector<int>>& graph, vector<int>& outdeg, vector<bool>& visited, set<pair<int,int>>& oriented_edges)
{
	visited[node] = 1;
	for (int neighbor: graph[node])
	{
		if (neighbor == parent)
			continue;
		
		bool is_oriented =	oriented_edges.find({ node, neighbor }) != oriented_edges.end() || 
							oriented_edges.find({neighbor, node}) != oriented_edges.end();
		if (visited[neighbor] && !is_oriented)
		{
			oriented_edges.insert({ node, neighbor });
			outdeg[node]++;
		}
		if (!visited[neighbor])
		{
			dfs(neighbor, node, graph, outdeg, visited, oriented_edges);
			if (outdeg[neighbor] % 2 == 0)
			{
				oriented_edges.insert({ node,neighbor });
				outdeg[node]++;
			}
			else
			{
				oriented_edges.insert({ neighbor, node });
				outdeg[neighbor]++;
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int node_cnt, edge_cnt; cin >> node_cnt >> edge_cnt;
	vector<vector<int>> graph(node_cnt, vector<int>());
	for (int i = 0; i < edge_cnt; i++)
	{
		int a, b; cin >> a >> b;
		a--; b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	if (edge_cnt % 2 == 1)
		cout << "IMPOSSIBLE";
	else
	{
		vector<bool> visited(node_cnt);
		vector<int> outdeg(node_cnt);
		set<pair<int, int>> oriented_edges;
		for (int i = 0; i < node_cnt; i++)
		{
			if (!visited[i])
			{
				dfs(i, -1, graph, outdeg, visited, oriented_edges);
				if (oriented_edges.size() % 2 == 1)
				{
					cout << "IMPOSSIBLE";
					return 0;
				}
			}
		}
		
		for (auto e : oriented_edges)
			cout << e.first+1 << " " << e.second+1 << "\n";
	}
	return 0;
}