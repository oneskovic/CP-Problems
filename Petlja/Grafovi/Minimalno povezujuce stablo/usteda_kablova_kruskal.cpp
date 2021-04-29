#include <algorithm>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <tuple>
#include <vector>
using namespace std;
typedef long long ll;

class DSU
{
public:
	DSU(int max_element);
	void join_sets(int element1, int element2);
	int find_set(int element);
private:
	vector<int> representative;
	vector<int> rank;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int node_cnt, edge_cnt;
	cin >> node_cnt >> edge_cnt;
	vector<tuple<double, int, int>> edges;
	edges.reserve(edge_cnt);
	for (int i = 0; i < edge_cnt; i++)
	{
		int a, b;
		double w;
		cin >> a >> b >> w;
		edges.emplace_back(w, a, b);
	}
	
	sort(edges.begin(), edges.end());
	DSU mst = DSU(node_cnt);
	int taken_edges = 0;
	double total_weight = 0;
	for (int i = 0; i < edge_cnt && taken_edges < edge_cnt-1; i++)
	{
		double weight = get<0>(edges[i]);
		int node1 = get<1>(edges[i]), node2 = get<2>(edges[i]);
		if (mst.find_set(node1) != mst.find_set(node2))
		{
			taken_edges++;
			total_weight += weight;
			mst.join_sets(node1, node2);
		}
	}
	cout << setprecision(1) << fixed << total_weight;
	return 0;
}

DSU::DSU(int element_cnt)
{
	representative = vector<int>(element_cnt);
	rank = vector<int>(element_cnt, 1);
	iota(representative.begin(), representative.end(), 0);
}

void DSU::join_sets(int element1, int element2)
{
	int set1 = find_set(element1);
	int set2 = find_set(element2);
	if (rank[set1] > rank[set2])
		swap(set1, set2);
	
	// rank[set1] <= rank[set2]
	representative[set1] = set2;
	if (rank[set1] == rank[set2])
		rank[set1]++;
}

int DSU::find_set(int element)
{
	if (representative[element] == element)
		return element;
	return representative[element] = find_set(representative[element]);
}
