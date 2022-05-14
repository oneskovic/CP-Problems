#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;

class SegmentTree
{
public:
	SegmentTree(const vector<ll>& v);
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

	int n; cin >> n;
	vector<ll> segment_lengths(n);
	vector<ll> centers(n);
	for (int i = 0; i < n; i++)
	{
		ll left, right;
		cin >> left >> right;
		segment_lengths[i] = right - left;
		centers[i] = left + right; // not a bug
	}

	vector<pair<ll, int>> sorted_center_index_pair(n);
	for (int i = 0; i < n; i++)
	{
		sorted_center_index_pair[i] = { centers[i],i };
	}
	sort(sorted_center_index_pair.begin(), sorted_center_index_pair.end());
	vector<ll> sorted_centers(n);
	vector<ll> position_in_sorted_centers(n);
	for (int i = 0; i < n; i++)
	{
		sorted_centers[i] = sorted_center_index_pair[i].first;
		position_in_sorted_centers[sorted_center_index_pair[i].second] = i;
	}
	auto sorted_centers_tree = SegmentTree(vector<ll>(n));

	vector<pair<ll, int>> jaje(n);
	for (int i = 0; i < n; i++)
	{
		jaje[i] = { segment_lengths[i], i };
	}
	sort(jaje.begin(), jaje.end(), greater<pair<ll,int>>());

	ll solution = 0;
	for (int i = 0; i < n; i++)
	{
		ll center = centers[jaje[i].second];
		ll len = jaje[i].first;
		int left_boundary = lower_bound(sorted_centers.begin(),sorted_centers.end(), center - len) - sorted_centers.begin();
		int right_boundary = upper_bound(sorted_centers.begin(), sorted_centers.end(), center + len) - sorted_centers.begin();
		
		ll count_between = sorted_centers_tree.sum_query(left_boundary, right_boundary);
		int pos_in_sorted = position_in_sorted_centers[jaje[i].second];
		sorted_centers_tree.update(pos_in_sorted, 1);
		solution += count_between;
	}
	cout << solution << "\n";

	return 0;
}

SegmentTree::SegmentTree(const vector<ll>& elements)
{
	element_cnt = elements.size();
	tree = vector<ll>(2 * element_cnt);
	copy(elements.begin(), elements.end(), tree.begin() + element_cnt);
	for (int i = element_cnt - 1; i >= 0; i--)
	{
		tree[i] = tree[2 * i] + tree[2 * i + 1];
	}
}

ll SegmentTree::sum_query(int l, int r)
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

void SegmentTree::update(int pos, ll new_value)
{
	pos += element_cnt;
	tree[pos] = new_value;
	pos /= 2;
	while (pos > 0)
	{
		tree[pos] = tree[2 * pos] + tree[2 * pos + 1];
		pos /= 2;
	}
}