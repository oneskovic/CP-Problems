#include <algorithm>
#include <iostream>
#include <limits.h>
#include <vector>
using namespace std;
typedef long long ll;

class SegmentTree
{
public:
	SegmentTree(const vector<ll>& elements);
	pair<ll, ll> query_max(int l, int r);
	void update_element(int position, ll new_value, ll prev_element);
	vector<ll> element_from_which_max;
private:
	vector<ll> tree;
	int element_count;
};

int find_mapped_value(ll real_value, const vector<ll>& elements_sorted)
{
	auto lb = lower_bound(elements_sorted.begin(), elements_sorted.end(), real_value);
	int pos = lb - elements_sorted.begin();
	return pos;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int n; ll d;
	cin >> n >> d;
	vector<ll> elements(n);
	for (size_t i = 0; i < n; i++)
		cin >> elements[i];

	// Find element positions when sorted
	vector<pair<ll, int>> element_original_pos(n);
	for (size_t i = 0; i < n; i++)
		element_original_pos[i] = { elements[i],i };
	sort(element_original_pos.begin(), element_original_pos.end());
	vector<ll> elements_sorted = elements;
	vector<int> position_when_sorted(n);
	for (int i = 0; i < n; i++)
	{
		elements_sorted[i] = element_original_pos[i].first;
		int original_pos = element_original_pos[i].second;
		position_when_sorted[original_pos] = i;
	}

	auto tree = SegmentTree(vector<ll>(n));
	vector<ll> element_from_which_max = vector<ll>(n);
	for (int i = n-1; i >= 0; i--)
	{
		ll current_value = elements[i];
		int left = find_mapped_value(current_value - d, elements_sorted);
		int right = find_mapped_value(current_value + d, elements_sorted);
		
		auto query_left = tree.query_max(0, left);
		auto query_right = tree.query_max(right, n);
		ll max_sequence_to_continue = 0;
		ll max_element_query = -1;
		if (query_left.first > query_right.first)
		{
			max_sequence_to_continue = query_left.first;
			max_element_query = query_left.second;
		}
		else
		{
			max_sequence_to_continue = query_right.first;
			max_element_query = query_right.second;
		}
		if (max_sequence_to_continue == 0)
		{
			max_element_query = -1;
		}
		element_from_which_max[i] = max_element_query;
		tree.update_element(position_when_sorted[i], max_sequence_to_continue + 1, i);
	}

	auto solution_query = tree.query_max(0, n);
	cout << solution_query.first << "\n";
	int position = solution_query.second;
	while (position > -1)
	{
		cout << position + 1 << " ";
		position = element_from_which_max[position];
	}

	return 0;
}

SegmentTree::SegmentTree(const vector<ll>& elements)
{
	element_count = elements.size();
	element_from_which_max = vector<ll>(2*element_count, -1);
	tree = vector<ll>(2*element_count);
	for (int i = 0; i < element_count; i++)
		element_from_which_max[element_count + i] = i;
	
	copy(elements.begin(), elements.end(), tree.begin() + element_count);

	for (int i = element_count - 1; i > 0; i--)
	{
		if (tree[i*2] > tree[i*2+1])
		{
			tree[i] = tree[i * 2];
			element_from_which_max[i] = element_from_which_max[i * 2];
		}
		else
		{
			tree[i] = tree[i * 2 + 1];
			element_from_which_max[i] = element_from_which_max[i * 2 + 1];
		}
	}
}

pair<ll,ll> SegmentTree::query_max(int l, int r)
{
	l += element_count;
	r += element_count;
	ll max_in_range = LLONG_MIN;
	ll el_from_which_max = -1;
	while (l < r)
	{
		if (l % 2 == 1)
		{
			if (tree[l] > max_in_range)
			{
				max_in_range = tree[l];
				el_from_which_max = element_from_which_max[l];
			}
			l++;
		}
		if (r % 2 == 1)
		{
			r--;
			if (tree[r] > max_in_range)
			{
				max_in_range = tree[r];
				el_from_which_max = element_from_which_max[r];
			}
		}
		
		l /= 2;
		r /= 2;
	}
	return { max_in_range, el_from_which_max };
}

void SegmentTree::update_element(int position, ll new_value, ll prev_element)
{
	position += element_count;
	tree[position] = new_value;
	element_from_which_max[position] = prev_element;
	for (int i = position / 2; i > 0; i /= 2)
	{
		tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
		if (tree[i*2] > tree[i*2+1])
		{
			tree[i] = tree[i * 2];
			element_from_which_max[i] = element_from_which_max[i * 2];
		}
		else
		{
			tree[i] = tree[i * 2 + 1];
			element_from_which_max[i] = element_from_which_max[i * 2 + 1];
		}
	}
}
