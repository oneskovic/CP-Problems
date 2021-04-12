#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

class SegmentTree
{
public:
	SegmentTree(const vector<ll>& elements);
	SegmentTree();
	ll min_query(int l, int r);
	void update_value(int position, ll new_value);
private:
	vector<ll> tree;
	int element_count;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<int> elements(n);
	for (size_t i = 0; i < n; i++)
		cin >> elements[i];
	auto tree = SegmentTree(vector<ll>(n, 0));
	ll sol = 0;
	for (int i = n-2; i >= 0; i--)
	{
		sol += tree.min_query(i+1,)
	}

	return 0;
}

SegmentTree::SegmentTree(const vector<ll>& elements)
{
	element_count = elements.size();
	tree = vector<ll>(element_count * 2);
	copy(elements.begin(), elements.end(), tree.begin() + element_count);

	for (int i = element_count - 1; i > 0; i--)
		tree[i] = min(tree[2 * i], tree[2 * i + 1]);
}

SegmentTree::SegmentTree()
{
}

ll SegmentTree::min_query(int l, int r)
{
	l += element_count;
	r += element_count;
	ll max_el = LLONG_MIN;
	while (l < r)
	{
		if (l % 2 == 1)
		{
			max_el = min(max_el, tree[l++]);
		}
		if (r % 2 == 1)
		{
			max_el = min(max_el, tree[--r]);
		}
		l /= 2;
		r /= 2;
	}
	return max_el;
}

void SegmentTree::update_value(int position, ll new_value)
{
	position += element_count;
	tree[position] = new_value;
	for (int i = position / 2; i > 0; i /= 2)
		tree[i] = min(tree[2 * i], tree[2 * i + 1]);
}
