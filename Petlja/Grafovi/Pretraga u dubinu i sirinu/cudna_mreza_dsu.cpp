#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class DSU
{
public:
	DSU(int max_node_count);
	void make_set(int n);
	/// <summary>
	/// Joins the two sets that node1 and node2 belong to
	/// </summary>
	void union_sets(int node1, int node2);
	int find_representative(int node);
private:
	vector<int> set_id, size_of_set;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int server_price, connection_price;
	cin >> server_price >> connection_price;
	int node_count, edge_count;
	cin >> node_count >> edge_count;

	vector<pair<int, int>> edges; edges.reserve(edge_count);

	for (size_t i = 0; i < edge_count; i++)
	{
		int a, b;
		cin >> a >> b;
		edges.push_back({ a,b });
	}

	if (server_price <= connection_price)
	{
		cout << server_price * node_count << "\n";
	}
	else
	{
		DSU node_component = DSU(node_count);
		for (size_t i = 0; i < node_count; i++)
			node_component.make_set(i);
		
		int mst_edge_count = 0;
		int component_count = node_count;
		for (auto edge: edges)
		{
			int a = edge.first;
			int b = edge.second;
			if (node_component.find_representative(a) != node_component.find_representative(b))
			{
				node_component.union_sets(a, b);
				mst_edge_count++;
				component_count--;
			}
		}

		cout << server_price*component_count + connection_price*mst_edge_count << "\n";
	}

	return 0;
}

DSU::DSU(int max_node_count)
{
	set_id = vector<int>(max_node_count);
	size_of_set = vector<int>(max_node_count);
}

void DSU::make_set(int n)
{
	size_of_set[n] = 1;
	set_id[n] = n;
}

void DSU::union_sets(int node1, int node2)
{
	int representative1 = find_representative(node1);
	int representative2 = find_representative(node2);
	// Join the smaller set to the larger set
	if (size_of_set[representative1] < size_of_set[representative2])
	{
		set_id[representative1] = representative2;
		size_of_set[representative1] += size_of_set[representative2];
	}
	else
	{
		set_id[representative2] = representative1;
		size_of_set[representative2] += size_of_set[representative1];
	}
}

int DSU::find_representative(int node)
{
	if (set_id[node] == node)
		return node;
	set_id[node] = find_representative(set_id[node]);
	return set_id[node];
}
