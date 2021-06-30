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
	vector<int> size, representative;
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
	size = vector<int>(max_cnt, 1);
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
	if (size[set2] > size[set1])
	{
		swap(set1, set2);
	}
	// size[set2] <= size[set1]
	representative[set2] = set1;
	size[set1] += size[set2];
}

int DSU::size_of_set(int element)
{
	int representative = find_set(element);
	return size[representative];
}
