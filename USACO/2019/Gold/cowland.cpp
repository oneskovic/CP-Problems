#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <limits.h>
using namespace std;
typedef long long ll;

class XorSegmentTree
{
public:
	XorSegmentTree(const vector<ll>& elements);
	void update(int position, ll value);
	ll xor_query(int l, int r);
private:
	vector<ll> tree;
	int element_cnt;
};

class MinSegmentTree
{
public:
	MinSegmentTree(const vector<pair<int, int>>& elements);
	int min_query(int l, int r);
private:
	int element_cnt;
	vector<pair<int,int>> tree;
};

void make_euler_tour_lca(int node, int parent, int height, const vector<vector<int>>& tree, vector<int>& first_occurance_euler, vector<pair<int,int>>& heights)
{
	first_occurance_euler[node] = heights.size();
	heights.emplace_back(height, node);
	for (int neighbor: tree[node])
	{
		if (neighbor != parent)
		{
			heights.emplace_back(height, node);
			make_euler_tour_lca(neighbor, node, height+1, tree, first_occurance_euler, heights);
		}
	}
}

void make_euler_tour_xor(int node, int parent, int& nodes_in_tour, const vector<vector<int>>& tree, vector<pair<int,int>>& subtree_range)
{
	subtree_range[node].first = nodes_in_tour;
	nodes_in_tour++;
	for (int neighbor: tree[node])
	{
		if (neighbor != parent)
		{
			make_euler_tour_xor(neighbor, node, nodes_in_tour, tree, subtree_range);
		}
	}
	subtree_range[node].second = nodes_in_tour;
	nodes_in_tour++;
}

void dfs_parents(int node, int parent, const vector<vector<int>>& tree, vector<int>& parent_vec)
{
	parent_vec[node] = parent;
	for (int neighbor: tree[node])
	{
		if (neighbor != parent)
		{
			dfs_parents(neighbor, node, tree, parent_vec);
		}
	}
}

int main()
{
	freopen("cowland.in", "r", stdin);
	freopen("cowland.out", "w", stdout);

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

	vector<pair<int,int>> heights; heights.reserve(n);
	vector<int> first_occurance_euler(n);
	make_euler_tour_lca(0, -1, 0, tree, first_occurance_euler, heights);
	MinSegmentTree lca_tree(heights);
	
	vector<int> parent_of_node(n);
	dfs_parents(0, -1, tree, parent_of_node);

	int temp = 0;
	vector<pair<int, int>> subtree_range(n);
	make_euler_tour_xor(0, -1, temp, tree, subtree_range);
	vector<ll> flattened_tree(2 * n);
	for (int node = 0; node < n; node++)
	{
		flattened_tree[subtree_range[node].first] = node_value[node];
		flattened_tree[subtree_range[node].second] = node_value[node];
	}
	XorSegmentTree xor_tree(flattened_tree);

	for (int i = 0; i < q; i++)
	{
		int type; cin >> type;
		if (type == 1)
		{
			int node; ll new_value; cin >> node >> new_value;
			node--;

			xor_tree.update(subtree_range[node].first, new_value);
			xor_tree.update(subtree_range[node].second, new_value);
		}
		else
		{
			int node1, node2; cin >> node1 >> node2;
			node1--; node2--;
			if (node1 == node2)
			{
				ll result = xor_tree.xor_query(0, subtree_range[node1].first + 1);
				if (parent_of_node[node1] != -1)
				{
					result ^= xor_tree.xor_query(0, subtree_range[parent_of_node[node1]].first+1);
				}
				cout << result << "\n";
				continue;
			}
			int l = min(first_occurance_euler[node1], first_occurance_euler[node2]);
			int r = max(first_occurance_euler[node1], first_occurance_euler[node2]);
			int lca = lca_tree.min_query(l,r);
			ll solution = 0;
			solution = xor_tree.xor_query(0, subtree_range[node1].first + 1);
			solution ^= xor_tree.xor_query(0, subtree_range[node2].first + 1);

			int node_above_lca = parent_of_node[lca];
			ll temp = xor_tree.xor_query(0, subtree_range[lca].first + 1);
			if (node_above_lca != -1)
			{
				temp ^= xor_tree.xor_query(0, subtree_range[node_above_lca].first + 1);
			}
			solution ^= temp;
			cout << solution << "\n";
		}
	}

	return 0;
}

XorSegmentTree::XorSegmentTree(const vector<ll>& elements)
{
	element_cnt = elements.size();
	tree = vector<ll>(2 * element_cnt);
	copy(elements.begin(), elements.end(),tree.begin()+element_cnt);
	for (int i = element_cnt - 1; i > 0; i--)
		tree[i] = (tree[2*i] ^ tree[2 * i + 1]);
}

void XorSegmentTree::update(int position, ll value)
{
	position += element_cnt;
	tree[position] = value;
	for (int i = position/2; i > 0; i/=2)
		tree[i] = (tree[2 * i] ^ tree[2 * i + 1]);
}

ll XorSegmentTree::xor_query(int l, int r)
{
	l += element_cnt;
	r += element_cnt;
	ll solution = 0;
	while (l < r)
	{
		if (l % 2 == 1)
		{
			solution ^= tree[l++];
		}
		if (r % 2 == 1)
		{
			solution ^= tree[--r];
		}
		l /= 2;
		r /= 2;
	}
	return solution;
}

MinSegmentTree::MinSegmentTree(const vector<pair<int,int>>& elements)
{
	element_cnt = elements.size();
	tree = vector<pair<int,int>>(2 * element_cnt);
	copy(elements.begin(), elements.end(), tree.begin() + element_cnt);
	for (int i = element_cnt - 1; i > 0; i--)
	{
		tree[i] = min(tree[2 * i], tree[2 * i + 1]);
	}
}

int MinSegmentTree::min_query(int l, int r)
{
	l += element_cnt;
	r += element_cnt;
	pair<int, int> solution = { INT_MAX,INT_MAX };
	while (l < r)
	{
		if (l % 2 == 1)
		{
			solution = min(solution, tree[l++]);
		}
		if (r % 2 == 1)
		{
			solution = min(solution, tree[--r]);
		}
		l /= 2;
		r /= 2;
	}
	return solution.second;
}
