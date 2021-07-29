#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

typedef long long ll;

class SegmentTree
{
public:
	SegmentTree(const vector<ll>& elements);
	void range_assign(int l, int r, ll new_value);
	ll range_bitwise_or(int l, int r);
private:
	void assign_to_node(int node, ll new_value);
	void push_from_parents(int node);
	void update_parents(int node);
	vector<ll> tree, delayed;
	int element_cnt;
};

void make_euler_tour(int node, int parent, vector<vector<int>>& tree, const vector<ll>& node_values, vector<pair<int, int>>& subtree_range, vector<ll>& euler_nodes)
{
	subtree_range[node].first = euler_nodes.size();
	euler_nodes.push_back(node_values[node]);
	for (int neighbor: tree[node])
	{
		if (neighbor != parent)
		{
			make_euler_tour(neighbor, node, tree, node_values, subtree_range, euler_nodes);
		}
	}
	subtree_range[node].second = euler_nodes.size();
	euler_nodes.push_back(node_values[node]);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int node_cnt, query_cnt; cin >> node_cnt >> query_cnt;
	vector<ll> node_values(node_cnt);
	for (int i = 0; i < node_cnt; i++)
	{
		cin >> node_values[i];
		node_values[i] = ((ll)1 << node_values[i]);
	}
	vector<vector<int>> tree(node_cnt, vector<int>());
	for (int i = 0; i < node_cnt-1; i++)
	{
		int a, b; cin >> a >> b;
		a--; b--;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}
	vector<pair<int, int>> subtree_range(node_cnt);
	vector<ll> flattened_tree; flattened_tree.reserve(2 * node_cnt);
	make_euler_tour(0, -1, tree, node_values, subtree_range, flattened_tree);
	SegmentTree segment_tree(flattened_tree);
	for (int i = 0; i < query_cnt; i++)
	{
		int type; cin >> type;
		if (type == 1)
		{
			int vertex, new_color; cin >> vertex >> new_color;
			vertex--;
			ll new_value = ((ll)1 << new_color);
			segment_tree.range_assign(subtree_range[vertex].first, subtree_range[vertex].second + 1, new_value);
		}
		else
		{
			int vertex; cin >> vertex;
			vertex--;
			ll range_or = segment_tree.range_bitwise_or(subtree_range[vertex].first, subtree_range[vertex].second + 1);

			int solution = 0;
			ll mask = 1;
			for (int i = 0; i < 61; i++)
			{
				solution += (bool)(range_or & mask);
				mask <<= 1;
			}
			cout << solution << "\n";
		}
	}


	return 0;
}

SegmentTree::SegmentTree(const vector<ll>& elements)
{
	element_cnt = elements.size();
	tree = vector<ll>(2 * element_cnt);
	delayed = tree;
	copy(elements.begin(), elements.end(), tree.begin() + element_cnt);
	for (int i = element_cnt - 1; i > 0; i--)
		tree[i] = (tree[2 * i] | tree[2 * i + 1]);
}

void SegmentTree::range_assign(int l, int r, ll new_value)
{
	l += element_cnt;
	r += element_cnt;
	push_from_parents(l);
	push_from_parents(r-1);
	int l0 = l, r0 = r;
	while (l < r)
	{
		if (l % 2 == 1)
		{
			assign_to_node(l++, new_value);
		}
		if (r % 2 == 1)
		{
			assign_to_node(--r, new_value);
		}
		l /= 2;
		r /= 2;
	}
	update_parents(l0);
	update_parents(r0-1);
}

ll SegmentTree::range_bitwise_or(int l, int r)
{
	l += element_cnt;
	r += element_cnt;
	push_from_parents(l);
	push_from_parents(r - 1);
	ll result = 0;
	while (l < r)
	{
		if (l % 2 == 1)
		{
			result |= tree[l++];
		}
		if (r % 2 == 1)
		{
			result |= tree[--r];
		}
		l /= 2;
		r /= 2;
	}
	return result;
}

void SegmentTree::assign_to_node(int node, ll new_value)
{
	tree[node] = new_value;
	delayed[node] = new_value;
}

void SegmentTree::push_from_parents(int node)
{
	stack<int> parents;
	for (int i = node/2; i > 0; i/=2)
	{
		parents.push(i);		
	}
	while (!parents.empty())
	{
		int i = parents.top();
		parents.pop();
		if (delayed[i] != 0)
		{
			assign_to_node(i * 2, delayed[i]);
			assign_to_node(i * 2 + 1, delayed[i]);
			delayed[i] = 0;
		}
	}
}

void SegmentTree::update_parents(int node)
{
	for (int i = node/2; i > 0; i/=2)
	{
		tree[i] = delayed[i] == 0 ? (tree[i * 2] | tree[i * 2 + 1]) : delayed[i];
	}
}
