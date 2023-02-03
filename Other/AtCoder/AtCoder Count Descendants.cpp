#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;

class SegmentTree
{
public:
	SegmentTree(const vector<ll>& elements);
	SegmentTree(int n);
	void update(int position, ll new_value);
	ll sum_query(int l, int r);
private:
	int element_count;
	vector<ll> tree;
};

struct query
{
	int id, node;
};

void dfs_euler(int node, const vector<vector<int>>& children, vector<int>& euler_start, vector<int>& euler_end, int& euler_cnt)
{
	euler_start[node] = euler_cnt++;
	for (int child: children[node])
		dfs_euler(child, children, euler_start, euler_end, euler_cnt);
	euler_end[node] = euler_cnt;
}

void dfs_depth(int node, const vector<vector<int>>& children, map<int, vector<int>>& depth, int current_depth = 0)
{
	if (depth.find(current_depth) == depth.end())
		depth[current_depth] = vector<int>();
	
	depth[current_depth].push_back(node);
	for (int child: children[node])
		dfs_depth(child, children, depth, current_depth + 1);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<vector<int>> children(n, vector<int>());
	for (int i = 0; i < n-1; i++)
	{
		int parent; cin >> parent;
		parent--;
		children[parent].push_back(i+1);
	}
	vector<int> euler_start(n);
	vector<int> euler_end(n);

	int query_cnt; cin >> query_cnt;
	map<int, vector<query>> queries;
	for (int i = 0; i < query_cnt; i++)
	{
		int node, dist_from_root;
		cin >> node >> dist_from_root;
		node--;
		if (queries.find(dist_from_root) == queries.end())
			queries[dist_from_root] = vector<query>();
		queries[dist_from_root].push_back({ i, node });
	}
	int euler_cnt = 0;
	dfs_euler(0, children, euler_start, euler_end, euler_cnt);
	map<int, vector<int>> nodes_at_depth;
	dfs_depth(0, children, nodes_at_depth);

	vector<int> solution(query_cnt);
	SegmentTree tree(n);
	for (auto& kvp: queries)
	{
		int depth = kvp.first;
		for (int node: nodes_at_depth[depth])
			tree.update(euler_start[node], 1);
		
		for (auto q: kvp.second)
			solution[q.id] = tree.sum_query(euler_start[q.node], euler_end[q.node]);

		for (int node : nodes_at_depth[depth])
			tree.update(euler_start[node], 0);
	}

	for (int x: solution)
		cout << x << "\n";

	return 0;
}

SegmentTree::SegmentTree(const vector<ll>& elements)
{
	element_count = elements.size();
	tree = vector<ll>(element_count * 2);
	copy(elements.begin(), elements.end(), tree.begin() + element_count);
	for (int i = element_count - 1; i > 0; i--)
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

SegmentTree::SegmentTree(int n)
{
	element_count = n;
	tree = vector<ll>(element_count * 2);
}

void SegmentTree::update(int position, ll new_value)
{
	position += element_count;
	tree[position] = new_value;
	for (int i = position / 2; i > 0; i /= 2)
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

ll SegmentTree::sum_query(int l, int r)
{
	l += element_count; r += element_count;
	ll sum = 0;
	while (l < r)
	{
		if (l % 2 == 1)
			sum += tree[l++];
		if (r % 2 == 1)
			sum += tree[--r];

		l /= 2; r /= 2;
	}
	return sum;
}