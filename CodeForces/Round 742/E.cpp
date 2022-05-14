#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#include <chrono>
using namespace std;

typedef long long ll;

class SegmentTree
{
public:
	SegmentTree(const vector<ll>& elements);
	void range_assign(int l, int r, ll new_value);
	ll range_sum(int l, int r);
private:
	void assign_to_node(int node, ll new_value);
	void push_from_parents(int node);
	void update_parents(int node);
	vector<ll> tree, delayed, interval_len;
	vector<bool> b;
	int element_cnt;
};

void test(vector<ll> v)
{
	int q = 1000;
	SegmentTree tree = SegmentTree(v);
	for (int i = 0; i < q; i++)
	{
		int a = rand() % v.size(), b = rand() % v.size();
		int l = min(a, b), r = max(a, b);
		if (rand()%2 == 0)
		{
			ll sum = 0;
			for (int i = l; i < r; i++)
			{
				sum += v[i];
			}
			ll segment_tree_sum = tree.range_sum(l, r);
			if (sum != segment_tree_sum)
			{
				cout << "WA\n";
			}
			else
				cout << "OK\n";
		}
		else
		{
			int new_val = rand() % 100 + 1;
			for (int i = l; i < r; i++)
			{
				v[i] = new_val;
			}
			tree.range_assign(l, r, new_val);
		}
	}
}

void update_to_right(int pos, ll new_val, ll val_right, SegmentTree& tree)
{
	if (val_right > new_val)
	{

	}
}

int main()
{
	srand(time(0));
	ios::sync_with_stdio(false);
	cin.tie(0);

	for (int t = 0; t < 1000; t++)
	{
		vector<ll> rand_vec(rand()%100+5);
		for (int i = 0; i < rand_vec.size(); i++)
		{
			rand_vec[i] = rand() % 100;
		}
		test(rand_vec);
	}

	int n, q; cin >> n >> q;
	vector<ll> is_start(n);
	vector<ll> elements(n);
	is_start[0] = 1;
	cin >> elements[0];
	for (int i = 1; i < n; i++)
	{
		cin >> elements[i];
		if (elements[i] < elements[i-1])
		{
			is_start[i] = 1;
		}
	}
	SegmentTree tree = SegmentTree(is_start);
	for (int i = 0; i < q; i++)
	{
		int type; cin >> type;
		if (type == 1)
		{
			int pos; cin >> pos;
			ll new_value; cin >> new_value;
			bool was_start = tree.range_sum(pos, pos + 1);
			bool was_end = pos == n-1 ? false : tree.range_sum(pos + 1, pos + 2);
			elements[pos] = new_value;
			pos--;
			

		}
		else
		{

		}
	}

	return 0;
}

SegmentTree::SegmentTree(const vector<ll>& elements)
{
	element_cnt = elements.size();
	tree = vector<ll>(2 * element_cnt);
	b = vector<bool>(2 * element_cnt);
	interval_len = tree;
	delayed = tree;
	copy(elements.begin(), elements.end(), tree.begin() + element_cnt);
	fill(interval_len.begin() + element_cnt, interval_len.end(), 1);
	for (int i = element_cnt - 1; i > 0; i--)
	{
		tree[i] = (tree[2 * i] + tree[2 * i + 1]);
		interval_len[i] = (interval_len[2 * i] + interval_len[2 * i + 1]);
	}
}

void SegmentTree::range_assign(int l, int r, ll new_value)
{
	l += element_cnt;
	r += element_cnt;
	push_from_parents(l);
	push_from_parents(r - 1);
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
	update_parents(r0 - 1);
}

ll SegmentTree::range_sum(int l, int r)
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
			result += tree[l++];
		}
		if (r % 2 == 1)
		{
			result += tree[--r];
		}
		l /= 2;
		r /= 2;
	}
	return result;
}

void SegmentTree::assign_to_node(int node, ll new_value)
{
	tree[node] = new_value * interval_len[node];
	delayed[node] = new_value;
	b[node] = 1;
}

void SegmentTree::push_from_parents(int node)
{
	stack<int> parents;
	for (int i = node / 2; i > 0; i /= 2)
	{
		parents.push(i);
	}
	while (!parents.empty())
	{
		int i = parents.top();
		parents.pop();
		if (b[i] != 0)
		{
			assign_to_node(i * 2, delayed[i]);
			assign_to_node(i * 2 + 1, delayed[i]);
			b[i] = 0;
		}
	}
}

void SegmentTree::update_parents(int node)
{
	for (int i = node / 2; i > 0; i /= 2)
	{
		tree[i] = b[i] == 0 ? (tree[i * 2] + tree[i * 2 + 1]) : delayed[i]*interval_len[i];
	}
}