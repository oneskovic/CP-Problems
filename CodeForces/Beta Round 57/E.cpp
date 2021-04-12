#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

class SegmentTree
{
public:
	SegmentTree(const vector<bool>& elements);
	void UpdateValue(int postion, bool new_value);
	ll Sum(int l, int r);
private:
	vector<ll> tree;
	int element_count;
};

vector<int> find_positions_when_sorted(const vector<ll>& elements)
{
	auto temp = vector<pair<ll, int>>(elements.size());
	for (size_t i = 0; i < elements.size(); i++)
	{
		temp[i] = { elements[i],i };
	}
	sort(temp.begin(), temp.end());
	vector<int> positions_when_sorted(elements.size());
	for (size_t i = 0; i < elements.size(); i++)
	{
		int original_pos = temp[i].second;
		positions_when_sorted[original_pos] = i;
	}
	return positions_when_sorted;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<ll> elements(n);
	for (size_t i = 0; i < n; i++)
		cin >> elements[i];

	auto positions_when_sorted = find_positions_when_sorted(elements);
	auto left_part_tree = SegmentTree(vector<bool>(elements.size(), 0));
	auto right_part_tree = SegmentTree(vector<bool>(elements.size(), 1));

	left_part_tree.UpdateValue(positions_when_sorted[0], 1);
	right_part_tree.UpdateValue(positions_when_sorted[0], 0);
	ll solution = 0;
	for (size_t i = 1; i < elements.size() - 1; i++)
	{
		right_part_tree.UpdateValue(positions_when_sorted[i], 0);
		ll count_larger_left = left_part_tree.Sum(positions_when_sorted[i], n);
		ll count_smaller_right = right_part_tree.Sum(0, positions_when_sorted[i]);
		solution += count_larger_left * count_smaller_right;

		left_part_tree.UpdateValue(positions_when_sorted[i], 1);
	}
	cout << solution;

	return 0;
}

SegmentTree::SegmentTree(const vector<bool>& elements)
{
	element_count = elements.size();
	tree = vector<ll>(element_count * 2);
	copy(elements.begin(), elements.end(), tree.begin() + element_count);
	for (int i = element_count - 1; i >= 1; i--)
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

void SegmentTree::UpdateValue(int position, bool new_value)
{
	position += element_count;
	tree[position] = new_value;
	position /= 2;
	while (position > 0)
	{
		tree[position] = tree[position * 2] + tree[position * 2 + 1];
		position /= 2;
	}
}

ll SegmentTree::Sum(int l, int r)
{
	l += element_count;
	r += element_count;
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
