#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
#define ll long long
/// <summary>
/// A simple sum query segment tree
/// </summary>
class SegmentTree
{
public:
	SegmentTree(const vector<ll>& elements);
	void Modify(int position, ll new_value);
	ll Query(int l, int r);
	int lower_bound(int l, int r, ll sum);
private:
	int element_count;
	vector<ll> tree;
};
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
	vector<ll> v = vector<ll>(n, 1);
	auto tree = SegmentTree(v);
	int prev_position = -1;
	int card_to_place = 1;
	ll sum_to_find = card_to_place + 1;
	vector<int> solution(n);
	while (card_to_place < n)
	{
		int lb_pos = tree.lower_bound(prev_position + 1, n, sum_to_find);
		ll found_sum = tree.Query(prev_position + 1, n);
		if (found_sum < sum_to_find)
		{
			prev_position = -1;
			sum_to_find -= found_sum;
			ll whole_array_sum = tree.Query(0, n);
			sum_to_find %= whole_array_sum;
			if (sum_to_find == 0)
				sum_to_find = whole_array_sum;
		}
		else
		{
			tree.Modify(lb_pos - 1, 0);
			solution[lb_pos-1] = card_to_place;
			card_to_place++;
			sum_to_find = card_to_place + 1;
			prev_position = lb_pos-1;
		}
	}

	for (int element : solution)
	{
		if (element == 0)
			cout << n;
		else
			cout << element;
		cout << " ";
	}
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

void SegmentTree::Modify(int position, ll new_value)
{
	position += element_count;
	tree[position] = new_value;
	for (int i = position / 2; i > 0; i /= 2)
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

ll SegmentTree::Query(int l, int r)
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

int SegmentTree::lower_bound(int l, int r, ll sum)
{
	int mid = -1;
	int start_position = l;
	while (l < r)
	{
		mid = (l + r) / 2;
		ll query_sum = Query(start_position, mid);

		if (query_sum >= sum)
			r = mid;

		else
			l = mid + 1;
	}
	return l;
}
