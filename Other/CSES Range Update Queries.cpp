#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

class SegmentTree
{
public:
	SegmentTree(const vector<ll>& elements);
	void update(int position, ll delta);
	ll query(int l, int r);
private:
	vector<ll> tree;
	int element_cnt;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int element_cnt, query_cnt; cin >> element_cnt >> query_cnt;
	vector<ll> elements(element_cnt);
	for (int i = 0; i < element_cnt; i++)
		cin >> elements[i];

	vector<ll> difference_vec(element_cnt);
	difference_vec[0] = elements[0];
	for (int i = 1; i < element_cnt; i++)
		difference_vec[i] = elements[i] - elements[i - 1];
	SegmentTree difference_tree(difference_vec);

	for (int i = 0; i < query_cnt; i++)
	{
		int type; cin >> type;
		if (type == 1)
		{
			int l, r; ll u; cin >> l >> r >> u;
			l--; r--;

			difference_tree.update(l, u);
			if (r+1 < element_cnt)
			{
				difference_tree.update(r + 1, -u);
			}
		}
		else
		{
			int position; cin >> position;
			cout << difference_tree.query(0, position) << "\n";
		}
	}
	return 0;
}

SegmentTree::SegmentTree(const vector<ll>& elements)
{
	element_cnt = elements.size();
	tree = vector<ll>(2 * element_cnt);
	copy(elements.begin(), elements.end(), tree.begin() + element_cnt);
	for (int i = element_cnt-1; i > 0; i--)
		tree[i] = tree[2 * i] + tree[2 * i + 1];
}

void SegmentTree::update(int position, ll delta)
{
	position += element_cnt;
	tree[position] += delta;
	for (int i = position/2; i > 0; i/=2)
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

ll SegmentTree::query(int l, int r)
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
