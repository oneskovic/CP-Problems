#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <limits.h>
using namespace std;
typedef long long ll;

class MinSegmentTree
{
public:
	MinSegmentTree(const vector<pair<int,int>>& elements);
	pair<int,int> min_query(int l, int r);
private:
	vector<pair<int, int>> tree;
	int element_cnt;
};

class SumSegmentTree
{
public:
	SumSegmentTree(const vector<int>& elements);
	ll sum_query(int l, int r);
	void update(int position, int new_value);
private:
	vector<ll> tree;
	int element_cnt;
};

void make_euler_tour_lca(const vector<vector<int>>& tree, int node, int parent, int height, vector<pair<int,int>>& height_node, vector<int>& firt_position_in_tour)
{
	firt_position_in_tour[node] = height_node.size();
	height_node.push_back({ height,node });
	for (int neighbor: tree[node])
	{
		if (neighbor != parent)
		{
			height_node.push_back({ height,node });
			make_euler_tour_lca(tree, neighbor, node, height + 1, height_node, firt_position_in_tour);
		}
	}
}

void make_euler_tour_min(const vector<vector<int>>& tree, int node, int parent, vector<pair<int, int>>& subtree_interval, vector<int>& tour_nodes)
{
	subtree_interval[node].first = tour_nodes.size();
	tour_nodes.push_back(0);
	for (int neighbor: tree[node])
	{
		if (neighbor != parent)
		{
			make_euler_tour_min(tree, neighbor, node, subtree_interval, tour_nodes);
		}
	}
	subtree_interval[node].second = tour_nodes.size();
	tour_nodes.push_back(0);
}

struct query
{
	int node1, node2;
	int index;
};

int main()
{
	//freopen("milkvisits.in", "r", stdin);
	//freopen("milkvisits.out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(0);

	int node_cnt, query_cnt; cin >> node_cnt >> query_cnt;
	vector<int> node_values(node_cnt);
	vector<vector<int>> value_node_map(node_cnt + 1, vector<int>());
	for (int i = 0; i < node_cnt; i++)
	{
		cin >> node_values[i];
		value_node_map[node_values[i]].push_back(i);
	}
	vector<vector<int>> tree(node_cnt, vector<int>());
	for (int i = 0; i < node_cnt-1; i++)
	{
		int a, b; cin >> a >> b;
		a--; b--;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}
	vector<pair<int,int>> height_node_pairs; height_node_pairs.reserve(node_cnt);
	vector<int> first_position_in_tour(node_cnt);
	make_euler_tour_lca(tree, 0, -1, 0, height_node_pairs, first_position_in_tour);
	MinSegmentTree lca_segment_tree(height_node_pairs);

	vector<int> flattened_tree; flattened_tree.reserve(2 * node_cnt);
	vector<pair<int, int>> subtree_interval(node_cnt);
	make_euler_tour_min(tree, 0, -1, subtree_interval, flattened_tree);
	SumSegmentTree sum_segment_tree(flattened_tree);
	vector<vector<query>> value_query_map(node_cnt+1,vector<query>());
	for (int i = 0; i < query_cnt; i++)
	{
		int a, b, val; cin >> a >> b >> val;
		a--; b--;
		value_query_map[val].push_back({ a,b,i });
	}

	string solution_string(query_cnt,'0');
	for (int val = 0; val < value_query_map.size(); val++)
	{
		for (int node: value_node_map[val])
		{
			sum_segment_tree.update(subtree_interval[node].first, 1);
			sum_segment_tree.update(subtree_interval[node].second, -1);
		}
		for (const auto& query: value_query_map[val])
		{
			int node1 = query.node1, node2 = query.node2;
			int l = min(first_position_in_tour[node1], first_position_in_tour[node2] + 1), 
				r = max(first_position_in_tour[node1], first_position_in_tour[node2] + 1);
			int lca = lca_segment_tree.min_query(l,r).second;
			ll sum_to_node_1 = sum_segment_tree.sum_query(0, subtree_interval[node1].first + 1);
			ll sum_to_node_2 = sum_segment_tree.sum_query(0, subtree_interval[node2].first + 1);
			ll sum_to_lca = sum_segment_tree.sum_query(0, subtree_interval[lca].first + 1);
			ll value_of_lca = sum_segment_tree.sum_query(subtree_interval[lca].first, subtree_interval[lca].first + 1);
			ll solution = sum_to_node_1 + sum_to_node_2 - 2 * sum_to_lca + value_of_lca;
			if (solution > 0)
			{
				solution_string[query.index] = 	'1';
			}
		}
		for (int node : value_node_map[val])
		{
			sum_segment_tree.update(subtree_interval[node].first, 0);
			sum_segment_tree.update(subtree_interval[node].second, 0);
		}
	}
	cout << solution_string << "\n";
	return 0;
}

MinSegmentTree::MinSegmentTree(const vector<pair<int,int>>& elements)
{
	element_cnt = elements.size();
	tree = vector<pair<int,int>>(2 * element_cnt);
	copy(elements.begin(), elements.end(), tree.begin() + element_cnt);
	for (int i = element_cnt - 1; i > 0; i--)
		tree[i] = min(tree[2 * i], tree[2 * i + 1]);
}

pair<int,int> MinSegmentTree::min_query(int l, int r)
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
	return solution;
}

SumSegmentTree::SumSegmentTree(const vector<int>& elements)
{
	element_cnt = elements.size();
	tree = vector<ll>(2*element_cnt);
	copy(elements.begin(), elements.end(), tree.begin() + element_cnt);
	for (int i = element_cnt - 1; i > 0; i--)
		tree[i] = tree[2 * i] + tree[2 * i + 1];
}

ll SumSegmentTree::sum_query(int l, int r)
{
	l += element_cnt;
	r += element_cnt;

	ll solution = 0;
	while (l < r)
	{
		if (l % 2 == 1)
		{
			solution += tree[l++];
		}
		if (r % 2 == 1)
		{
			solution += tree[--r];
		}
		l /= 2;
		r /= 2;
	}
	return solution;
}

void SumSegmentTree::update(int position, int new_value)
{
	position += element_cnt;
	tree[position] = new_value;
	for (int i = position/2; i > 0; i/=2)
		tree[i] = tree[2 * i] + tree[2 * i + 1];
}
