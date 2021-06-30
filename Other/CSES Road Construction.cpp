#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

class DSU
{
public:
	DSU(int max_cnt);
	int find_set(int element);
	void join_sets(int element1, int element2);
	int size_of_set(int element);
private:
	vector<int> representative;
	vector<vector<int>> elements_in_set;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int node_cnt, edge_cnt; cin >> node_cnt >> edge_cnt;
	DSU dsu(node_cnt);
	int component_cnt = node_cnt;
	int max_component_size = 1;
	for (int i = 0; i < edge_cnt; i++)
	{
		int a, b; cin >> a >> b;
		a--; b--;
		if (dsu.find_set(a) != dsu.find_set(b))
		{
			component_cnt--;
			dsu.join_sets(a, b);
			max_component_size = max(max_component_size,dsu.size_of_set(a));
		}
		cout << component_cnt << " " << max_component_size << "\n";
	}
	return 0;
}

DSU::DSU(int max_cnt)
{
	representative = vector<int>(max_cnt);
	iota(representative.begin(), representative.end(), 0);
	elements_in_set = vector<vector<int>>(max_cnt, vector<int>());
	for (int i = 0; i < max_cnt; i++)
		elements_in_set[i].push_back(i);
}

int DSU::find_set(int element)
{
	return representative[element];
}

void DSU::join_sets(int element1, int element2)
{
	int set1 = find_set(element1), set2 = find_set(element2);
	if (size_of_set(set2) > size_of_set(set1))
	{
		swap(set1, set2);
	}
	// size[set2] <= size[set1]
	for (int i : elements_in_set[set2])
	{
		elements_in_set[set1].push_back(i);
		representative[i] = set1;
	}
}

int DSU::size_of_set(int element)
{
	return elements_in_set[find_set(element)].size();
}

