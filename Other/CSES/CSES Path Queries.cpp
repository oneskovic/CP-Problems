#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

class SegmentTree
{
public:
	SegmentTree(const vector<ll>& elements);
	void update(int position, ll value);
	ll sum(int l, int r);
private:
	vector<ll> tree;
	int element_cnt;
};

void make_euler_tour(int node, int parent, int& nodes_in_tour, const vector<vector<int>>& tree, vector<pair<int,int>>& subtree_range)
{
	subtree_range[node].first = nodes_in_tour;
	nodes_in_tour++;

	for (int neighbor: tree[node])
	{
		if (neighbor != parent)
		{
			make_euler_tour(neighbor, node, nodes_in_tour, tree, subtree_range);
		}
	}

	subtree_range[node].second = nodes_in_tour;
	nodes_in_tour++;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int n,q; cin >> n >> q;
	vector<ll> node_value(n);
	for (int i = 0; i < n; i++)
		cin >> node_value[i];

	vector<vector<int>> tree(n, vector<int>());
	for (int i = 0; i < n-1; i++)
	{
		int a, b; cin >> a >> b; 
		a--; b--;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}
	vector<ll> flattened_tree(2*n);
	vector<pair<int, int>> subtree_range(n);

	int temp = 0;
	make_euler_tour(0, -1, temp, tree, subtree_range);
	for (int node = 0; node < n; node++)
	{
		ll node_val = node_value[node];
		flattened_tree[subtree_range[node].first] = node_val;
		flattened_tree[subtree_range[node].second] = -node_val;
	}
	SegmentTree segment_tree(flattened_tree);
	for (int i = 0; i < q; i++)
	{
		int type; cin >> type;
		if (type == 1)
		{
			int node,new_val; cin >> node >> new_val;
			node--;
			segment_tree.update(subtree_range[node].first, new_val);
			segment_tree.update(subtree_range[node].second, -new_val);
		}
		else
		{
			int node; cin >> node;
			node--;
			cout << segment_tree.sum(0, subtree_range[node].first + 1) << "\n";
		}
	}

	return 0;
}

SegmentTree::SegmentTree(const vector<ll>& elements)
{
	element_cnt = elements.size();
	tree = vector<ll>(2 * element_cnt);
	copy(elements.begin(), elements.end(),tree.begin()+element_cnt);
	for (int i = element_cnt - 1; i > 0; i--)
		tree[i] = tree[2*i] + tree[2 * i + 1];
}

void SegmentTree::update(int position, ll value)
{
	position += element_cnt;
	tree[position] = value;
	for (int i = position/2; i > 0; i/=2)
		tree[i] = tree[2 * i] + tree[2 * i + 1];
}

ll SegmentTree::sum(int l, int r)
{
	l += element_cnt;
	r += element_cnt;
	ll sum = 0;
	while (l < r)
	{
		if (l % 2 == 1)
		{
			sum += tree[l++];
		}
		if (r % 2 == 1)
		{
			sum += tree[--r];
		}
		l /= 2;
		r /= 2;
	}
	return sum;
}
