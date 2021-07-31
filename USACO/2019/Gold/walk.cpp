#include <algorithm>
#include <iostream>
#include <limits.h>
#include <numeric>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;
class DSU
{
public:
	DSU(int max_n);
	int find_set(int element);
	void join_sets(int element1, int element2);
private:
	vector<int> representative, size;
};

ll calculate_weight(ll x, ll y)
{
	return (2019201913 * x + 2019201949 * y) % 2019201997;
}

struct edge
{
	ll weight;
	int node1, node2;
	bool operator <(const edge& other)
	{
		return weight < other.weight;
	}
};
bool operator>(const edge& lhs, const edge& rhs)
{
	return lhs.weight > rhs.weight;
}

edge find_next_min_weight_edge(int node, int n, DSU& dsu)
{
	edge min_weight_edge = { LLONG_MAX,-1,-1 };
	for (int i = node+1; i < n; i++)
	{
		if (dsu.find_set(node) != dsu.find_set(i))
		{
			edge e = { calculate_weight(node+1,i+1),node,i };
			if (e.weight < min_weight_edge.weight)
			{
				min_weight_edge = e;
			}
		}
	}
	return min_weight_edge;
}

int main()
{
	freopen("walk.in", "r", stdin);
	freopen("walk.out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, k; cin >> n >> k;
	priority_queue<edge, vector<edge>, greater<edge>> min_weight_edge_from_node;
	DSU dsu(n);
	for (int i = 0; i < n; i++)
	{
		auto e = find_next_min_weight_edge(i, n, dsu);
		if (e.node1 != -1)
		{
			min_weight_edge_from_node.push(e);
		}
	}

	int group_cnt = n;
	while (!min_weight_edge_from_node.empty())
	{
		edge e = min_weight_edge_from_node.top();
		int n1 = e.node1, n2 = e.node2;
		if (dsu.find_set(n1) != dsu.find_set(n2))
		{
			if (group_cnt == k)
				break;
			
			group_cnt--;
			dsu.join_sets(n1, n2);
		}
		
		min_weight_edge_from_node.pop();
		edge new_edge = find_next_min_weight_edge(n1, n, dsu);
		if (new_edge.node1 != -1)
			min_weight_edge_from_node.push(new_edge);
	}
	if (!min_weight_edge_from_node.empty())
		cout << min_weight_edge_from_node.top().weight << "\n";	
	else
		cout << "0\n";
	return 0;
}

DSU::DSU(int max_n)
{
	representative = vector<int>(max_n);
	size = vector<int>(max_n, 1);
	iota(representative.begin(), representative.end(), 0);
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
	}
}
