#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

class SegmentTree
{
public:
	SegmentTree(int max_size);
	void update(int pos, ll new_val);
	ll sum_query(int l, int r);
private:
	int element_cnt;
	vector<ll> tree;
};

int minimize(const vector<int>& position_row, const vector<int>& position_col)
{
	int n = position_row.size();
	int sol = 0;
	for (int i = 0; i < n; i++)
	{
		if (position_row[i] < n)
			sol++;
	}
	for (int i = 0; i < position_col.size(); i++)
	{
		if (position_col[i] < n && position_row[position_col[i]] != i)
			sol++;
	}
	return sol;
}

ll maximize(const vector<int>& position_row, const vector<int>& position_col)
{
	vector<pair<int, int>> pos_row_sorted(position_row.size());
	for (int i = 0; i < position_row.size(); i++)
		pos_row_sorted[i] = { position_row[i] + 1,i };
	sort(pos_row_sorted.begin(), pos_row_sorted.end());
	int i = 0;

	auto tree = SegmentTree(position_row.size() + 1);
	ll sol = minimize(position_row, position_col);
	for (int col = 0; col < position_col.size(); col++)
	{
		while (i < pos_row_sorted.size() && pos_row_sorted[i].first == col)
		{
			int new_row = pos_row_sorted[i].second;
			tree.update(new_row, 1);
			i++;
		}
		sol += tree.sum_query(position_col[col]+1, position_row.size());
	}
	return sol;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m, t; cin >> n >> m >> t;
	vector<int> pos_in_row(n);
	for (int i = 0; i < n; i++)
		cin >> pos_in_row[i];

	vector<int> pos_in_col(m);
	for (int i = 0; i < m; i++)
		cin >> pos_in_col[i];
	
	if (t == 0)
		cout << minimize(pos_in_row, pos_in_col);
	else
		cout << maximize(pos_in_row, pos_in_col);

	return 0;
}

SegmentTree::SegmentTree(int max_size)
{
	element_cnt = max_size;
	tree = vector<ll>(2 * element_cnt);
}

void SegmentTree::update(int pos, ll new_val)
{
	pos += element_cnt;
	tree[pos] = new_val;
	for (int i = pos/2; i > 0; i/=2)
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

ll SegmentTree::sum_query(int l, int r)
{
	ll sum = 0;
	l += element_cnt;
	r += element_cnt;
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
