#include <algorithm>
#include <iostream>
#include <limits.h>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;

class SegmentTree
{
public:
	SegmentTree(int n);
	void update(int position, ll new_value);
	ll max_query(int l, int r);
private:
	int element_count;
	vector<ll> tree;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	map<int, vector<int>> element_positions;
	for (int i = 0; i < n; i++)
	{
		int val; cin >> val;
		if (element_positions.find(val) == element_positions.end())
			element_positions[val] = vector<int>();
		element_positions[val].push_back(i);
	}
	auto tree = SegmentTree(n);
	for (auto& kvp: element_positions)
	{
		vector<int> solutions; solutions.reserve(kvp.second.size());
		for (int pos: kvp.second)
		{
			int sol = tree.max_query(0, pos);
			solutions.push_back(sol + 1);
		}
		for (int i = 0; i < solutions.size(); i++)
		{
			int pos = kvp.second[i];
			tree.update(pos, solutions[i]);
		}
	}
	cout << tree.max_query(0, n);
	return 0;
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
		tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
}

ll SegmentTree::max_query(int l, int r)
{
	l += element_count; r += element_count;
	ll sol = LLONG_MIN;
	while (l < r)
	{
		if (l % 2 == 1)
			sol = max(sol, tree[l++]);
		if (r % 2 == 1)
			sol = max(sol, tree[--r]);

		l /= 2; r /= 2;
	}
	return sol;
}
