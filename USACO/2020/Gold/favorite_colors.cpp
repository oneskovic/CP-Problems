#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <queue>
#include <list>

using namespace std;

class DSU
{
public:
	DSU(int max_n, const vector<list<int>>& neighbors);
	int find_set(int element);
	void join_sets(int element1, int element2);
	vector<list<int>> neighbors;
	vector<int> set_color;
private:
	vector<int> representative, size;
};

queue<int> nodes_to_process;

void solve(vector<list<int>> neighbors)
{
	int node_cnt = neighbors.size();
	DSU dsu(node_cnt, neighbors);
	while (!nodes_to_process.empty())
	{
		int set = dsu.find_set(nodes_to_process.front());
		nodes_to_process.pop();
		if (dsu.neighbors[set].size() > 1)
		{
			int n1 = dsu.neighbors[set].back(); dsu.neighbors[set].pop_back();
			int n2 = dsu.neighbors[set].back();
			dsu.join_sets(n1, n2);
			if (dsu.neighbors[set].size() > 1)
			{
				nodes_to_process.push(set);
			}
		}
	}
	int current_color = 1;
	for (int node = 0; node < node_cnt; node++)
	{
		int set = dsu.find_set(node);
		if (dsu.set_color[set] == -1)
		{
			dsu.set_color[set] = current_color++;
		}
		cout << dsu.set_color[set] << "\n";
	}
}

int main()
{
	freopen("fcolor.in", "r", stdin);
	freopen("fcolor.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);

	int node_cnt, edge_cnt; cin >> node_cnt >> edge_cnt;
	vector<list<int>> neighbors(node_cnt);
	for (int i = 0; i < edge_cnt; i++)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;
		neighbors[a].push_back(b);
	}
	solve(neighbors);
	return 0;
}

DSU::DSU(int max_n, const vector<list<int>>& neighbors)
{
	representative = vector<int>(max_n);
	iota(representative.begin(), representative.end(), 0);
	size = vector<int>(max_n, 1);
	set_color = vector<int>(max_n, -1);
	for (int i = 0; i < max_n; i++)
		nodes_to_process.push(i);
	
	this->neighbors = neighbors;
}

int DSU::find_set(int element)
{
	if (representative[element] == element)
		return element;
	return representative[element] = find_set(representative[element]);
}

void DSU::join_sets(int element1, int element2)
{
	int set1 = find_set(element1), set2 = find_set(element2);
	if (set1 != set2)
	{
		if (size[set1] > size[set2])
			swap(set1, set2);
		
		// size[set1] <= size[set2]
		representative[set1] = set2;
		size[set2] += size[set1];
		neighbors[set2].splice(neighbors[set2].end(), neighbors[set1]);
		if (neighbors[set2].size() > 1)
		{
			nodes_to_process.push(set2);
		}
	}
}
