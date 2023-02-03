#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

class SegmentTree
{
public:
	SegmentTree(const vector<ll>& elements);
	void range_add(int l, int r, ll delta);
	ll query(int pos);
private:
	void update(int pos, ll delta);
	vector<ll> tree;
	int element_cnt;
};

SegmentTree::SegmentTree(const vector<ll>& elements)
{
	element_cnt = elements.size();
	vector<ll> diffs(element_cnt);
	diffs[0] = elements[0];
	for (int i = 1; i < element_cnt; i++)
		diffs[i] = elements[i] - elements[i - 1];
	
	tree = vector<ll>(2 * element_cnt);
	copy(diffs.begin(), diffs.end(), tree.begin() + element_cnt);
	for (int i = element_cnt-1; i > 0; i--)
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

void SegmentTree::range_add(int l, int r, ll delta)
{
	if (r < element_cnt)
		update(r, -delta);
	update(l, delta);
}

ll SegmentTree::query(int pos)
{
	int l = element_cnt, r = pos + element_cnt + 1;
	ll sol = 0;
	while (l < r)
	{
		if (l % 2 == 1)
			sol += tree[l++];
		
		if (r % 2 == 1)
			sol += tree[--r];
		
		l /= 2;
		r /= 2;
	}
	return sol;
}

void SegmentTree::update(int pos, ll delta)
{
	pos += element_cnt;
	tree[pos] += delta;
	for (int i = pos/2; i > 0; i/=2)
		tree[i] = tree[2 * i] + tree[2 * i + 1];
}
