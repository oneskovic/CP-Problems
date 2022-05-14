#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>
#include <map>
using namespace std;
typedef long long ll;

class SegmentTree
{
public:
	SegmentTree(const vector<int>& elements);
	void update(int position, int value);
	ll sum(int l, int r);
private:
	vector<int> tree;
	int element_cnt;
};

void euler_tour(int node, int parent, const vector<int>& node_values, const vector<vector<int>>& tree, vector<int>& tour_nodes, vector<pair<int,int>>& subtree_interval)
{
	tour_nodes.push_back(node_values[node]);
	subtree_interval[node].first = tour_nodes.size() - 1;
	for (int neighbor: tree[node])
	{
		if (neighbor != parent)
		{
			euler_tour(neighbor, node, node_values, tree, tour_nodes, subtree_interval);
		}
	}
	tour_nodes.push_back(node_values[node]);
	subtree_interval[node].second = tour_nodes.size() - 1;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<int> node_values(n);
	for (int i = 0; i < n; i++)
		cin >> node_values[i];

	vector<vector<int>> tree(n, vector<int>());
	for (int i = 0; i < n-1; i++)
	{
		int a, b; cin >> a >> b;
		a--; b--;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}
	
	vector<pair<int, int>> subtree_interval(n);
	vector<int> euler_tour_nodes; euler_tour_nodes.reserve(2 * n);
	euler_tour(0, -1, node_values, tree, euler_tour_nodes, subtree_interval);

	vector<tuple<int, int, int>> queries(n);
	for (int i = 0; i < n; i++)
		queries[i] = { subtree_interval[i].second,subtree_interval[i].first,i };
	
	sort(queries.begin(), queries.end());
	map<int, int> rightmost_position;
	SegmentTree rightmost_position_tree(vector<int>(euler_tour_nodes.size()));
	vector<int> solution(n);

	int j = 0;
	for (int i = 0; i < euler_tour_nodes.size(); i++)
	{
		int current_value = euler_tour_nodes[i];
		if (rightmost_position.find(current_value) != rightmost_position.end())
		{
			rightmost_position_tree.update(rightmost_position[current_value], 0);
		}
		rightmost_position[current_value] = i;
		rightmost_position_tree.update(i, 1);

		while (j < queries.size() && get<0>(queries[j]) == i)
		{
			int l = get<1>(queries[j]), r = get<0>(queries[j]);
			int original_pos = get<2>(queries[j]);
			int distinct_cnt = rightmost_position_tree.sum(l, r+1);
			solution[original_pos] = distinct_cnt;
			j++;
		}
	}
	for (int i: solution)
		cout << i << " ";
	cout << "\n";

	return 0;
}

SegmentTree::SegmentTree(const vector<int>& elements)
{
	element_cnt = elements.size();
	tree = vector<int>(2 * element_cnt);
	copy(elements.begin(), elements.end(), tree.begin() + element_cnt);
	for (int i = element_cnt - 1; i > 0; i--)
		tree[i] = tree[2 * i] + tree[2 * i + 1];
}

void SegmentTree::update(int position, int value)
{
	position += element_cnt;
	tree[position] = value;
	for (int i = position / 2; i > 0; i /= 2)
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
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
