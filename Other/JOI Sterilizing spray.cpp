#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;

class SegmentTree
{
public:
	SegmentTree(const vector<ll>& elements);
	ll sum_query(int l, int r);
	void update(int pos, ll new_value);
private:
	vector<ll> tree;
	int element_cnt;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, query_cnt, k; cin >> n >> query_cnt >> k;
	vector<ll> elements(n);
	set<int> nonzero_positions;
	for (int i = 0; i < n; i++)
	{
		cin >> elements[i];
		nonzero_positions.insert(i);
	}
	auto tree = SegmentTree(elements);
	
	for (int query_no = 0; query_no < query_cnt; query_no++)
	{
		int type; cin >> type;
		if (type == 1) // point update
		{
			int pos; cin >> pos;
			pos--;
			ll new_val; cin >> new_val;
			nonzero_positions.insert(pos);
			tree.update(pos, new_val);
			elements[pos] = new_val;
		}
		else if (type == 2) // range update
		{
			int l, r; cin >> l >> r;
			if (k == 1)
				continue;
			
			l--; r--;
			auto it = nonzero_positions.lower_bound(l);
			vector<int> zero_positions;
			while (it != nonzero_positions.end() && * it <= r)
			{
				int i = *it;
				elements[i] /= k;
				if (elements[i] == 0)
					zero_positions.push_back(i);
				tree.update(i, elements[i]);
				it++;
			}
			for (int i: zero_positions)
				nonzero_positions.erase(i);
		}
		else // range query
		{
			int l, r; cin >> l >> r;
			l--;
			ll sum = tree.sum_query(l, r);
			cout << sum << "\n";
		}
	}

	return 0;
}

SegmentTree::SegmentTree(const vector<ll>& elements)
{
	element_cnt = elements.size();
	tree = vector<ll>(2 * element_cnt);
	copy(elements.begin(), elements.end(), tree.begin() + element_cnt);
	for (int i = element_cnt - 1; i > 0; i--)
		tree[i] = tree[2 * i] + tree[2 * i + 1];
}

ll SegmentTree::sum_query(int l, int r)
{
	l += element_cnt;
	r += element_cnt;
	ll sum = 0;
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

void SegmentTree::update(int pos, ll new_value)
{
	pos += element_cnt;
	tree[pos] = new_value;
	for (int i = pos / 2; i > 0; i /= 2)
		tree[i] = tree[2 * i] + tree[2 * i + 1];
}
