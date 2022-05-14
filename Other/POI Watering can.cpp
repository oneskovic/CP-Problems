#include <algorithm>
#include <iostream>
#include <limits.h>
#include <numeric>
#include <vector>
using namespace std;
typedef long long ll;

class LazySegmentTree
{
public:
	LazySegmentTree(const vector<ll>& elements);
	pair<ll, int> max_query(int l, int r);
	void update(int l, int r, ll delta = 1);
private:
	void update_parents(int node);
	void push_delayed_from_parents(int node);
	vector<pair<ll, int>> tree;
	vector<ll> delayed;
	int element_cnt;
};

class SegmentTree
{
public:
	SegmentTree(const vector<int>& elements);
	void update(int pos, int new_val);
	int sum_query(int l, int r);
private:
	vector<int> tree;
	int element_cnt;
};

LazySegmentTree tree = LazySegmentTree({ 1 });
SegmentTree elements_over_limit_tree = SegmentTree({ 1 });
int limit = -1;
void inicjuj(int n, int k, int* D)
{
	vector<ll> elements(n);
	elements_over_limit_tree = SegmentTree(vector<int>(n));
	for (int i = 0; i < n; i++)
		elements[i] = D[i];
	tree = LazySegmentTree(elements);
	limit = k;

	auto query_res = tree.max_query(0, n);
	ll neg_inf = -1e9 - 1000;
	while (query_res.first >= limit)
	{
		elements_over_limit_tree.update(query_res.second, 1);
		tree.update(query_res.second, query_res.second + 1, neg_inf);
		query_res = tree.max_query(0, n);
	}
}
void podlej(int a, int b)
{
	tree.update(a, b+1);
	auto query_res = tree.max_query(a, b + 1);
	ll neg_inf = -1e9 - 1000;
	while (query_res.first >= limit)
	{
		elements_over_limit_tree.update(query_res.second, 1);
		tree.update(query_res.second, query_res.second + 1, neg_inf);
		query_res = tree.max_query(a, b + 1);
	}
}

int dojrzale(int a, int b)
{
	return elements_over_limit_tree.sum_query(a, b + 1);
}

LazySegmentTree::LazySegmentTree(const vector<ll>& elements)
{
	element_cnt = elements.size();
	tree = vector<pair<ll, int>>(2 * element_cnt);
	for (int i = element_cnt; i < 2*element_cnt; i++)
		tree[i] = { elements[i - element_cnt],i - element_cnt };
	delayed = vector<ll>(2 * element_cnt);
	for (int i = element_cnt - 1; i > 0; i--)
		tree[i] = max(tree[2 * i], tree[2 * i + 1]);
}

pair<ll, int> LazySegmentTree::max_query(int l, int r)
{
	l += element_cnt;
	r += element_cnt;
	push_delayed_from_parents(l);
	push_delayed_from_parents(r - 1);
	pair<ll, int> solution = { LLONG_MIN, -1 };
	while (l < r)
	{
		if (l % 2 == 1)
			solution = max(solution, tree[l++]);
		if (r % 2 == 1)
			solution = max(solution, tree[--r]);
		
		l /= 2;
		r /= 2;
	}
	return solution;
}

void LazySegmentTree::update(int l, int r, ll delta)
{
	l += element_cnt;
	r += element_cnt;
	int l0 = l, r0 = r;
	while (l < r)
	{
		if (l % 2 == 1)
		{
			delayed[l] += delta;
			tree[l].first += delta;
			l++;
		}
		if (r % 2 == 1)
		{
			r--;
			delayed[r] += delta;
			tree[r].first += delta;
		}
		l /= 2;
		r /= 2;
	}
	update_parents(l0);
	update_parents(r0-1);
}

void LazySegmentTree::update_parents(int node)
{
	for (int i = node/2; i > 0; i/=2)
	{
		tree[i] = max(tree[2 * i], tree[2 * i + 1]);
		tree[i].first += delayed[i];
	}
}

void LazySegmentTree::push_delayed_from_parents(int node)
{
	vector<int> parents;
	for (int i = node/2; i > 0; i/=2)
		parents.push_back(i);
	reverse(parents.begin(), parents.end());
	for (int i: parents)
	{
		tree[2 * i].first += delayed[i];
		delayed[2 * i] += delayed[i];
		tree[2 * i + 1].first += delayed[i];
		delayed[2 * i + 1] += delayed[i];
		delayed[i] = 0;
	}
}

SegmentTree::SegmentTree(const vector<int>& elements)
{
	element_cnt = elements.size();
	tree = vector<int>(2 * element_cnt);
	copy(elements.begin(), elements.end(), tree.begin() + element_cnt);
	for (int i = element_cnt - 1; i > 0; i--)
		tree[i] = tree[2 * i] + tree[2 * i + 1];
}

void SegmentTree::update(int pos, int new_val)
{
	pos += element_cnt;
	tree[pos] = new_val;
	for (int i = pos / 2; i > 0; i /= 2)
	{
		tree[i] = tree[2 * i] + tree[2 * i + 1];
	}
}

int SegmentTree::sum_query(int l, int r)
{
	l += element_cnt;
	r += element_cnt;
	int sum = 0;
	while (l < r)
	{
		if (l % 2 == 1)
			sum += tree[l++];
		if (r % 2 == 1)
			sum += tree[--r];
		
		l /= 2;
		r /= 2;
	}
	return sum;
}
