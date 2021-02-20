#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <unordered_map>
#include <chrono>
#include <random>
using namespace std;
#define ll long long

class SegmentTree
{
private:
	vector<int> tree;
	size_t element_count;
public:
	SegmentTree(const vector<int>& elements);
	void Update(int position, int new_value);
	int SumRange(int l, int r);
};

ll solve(vector<ll> elements, ll t)
{
	int n = elements.size();
	vector<ll> prefix_sums(n);
	partial_sum(elements.begin(), elements.end(), prefix_sums.begin());

	vector<int> place_in_sorted(n);
	vector<pair<ll,int>> temp = vector<pair<ll,int>>(n);
	for (size_t i = 0; i < n; i++)
		temp[i] = { prefix_sums[i],i };
	
	sort(temp.begin(), temp.end());
	vector<ll> sorted_prefixes(n);
	for (size_t i = 0; i < n; i++)
	{
		place_in_sorted[temp[i].second] = i;
		sorted_prefixes[i] = temp[i].first;
	}

	auto available_sum_tree = SegmentTree(vector<int>(n, 0));
	ll solution = 0;
	for (size_t i = 0; i < n; i++)
	{
		ll current_prefix_sum = prefix_sums[i];
		if (current_prefix_sum < t)
			solution++;

		ll needed_sum = current_prefix_sum - t;
		int smallest_left_sum_position = upper_bound(sorted_prefixes.begin(), sorted_prefixes.end(), needed_sum) - sorted_prefixes.begin();
		solution += available_sum_tree.SumRange(smallest_left_sum_position, n);

		int position_when_sorted = place_in_sorted[i];
		available_sum_tree.Update(position_when_sorted, 1);
	}
	return solution;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	ll n, t; cin >> n >> t;
	vector<ll> elements(n);
	for (size_t i = 0; i < n; i++)
		cin >> elements[i];
	cout << solve(elements, t);
	return 0;
}

SegmentTree::SegmentTree(const vector<int>& elements)
{
	element_count = elements.size();
	tree = vector<int>(2 * element_count);
	copy(elements.begin(), elements.end(), tree.begin() + element_count);
	for (int i = element_count-1; i >= 1; i--)
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

void SegmentTree::Update(int position, int new_value)
{
	position += element_count;
	tree[position] = new_value;
	for (int i = position/2; i >= 1; i/=2)
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

int SegmentTree::SumRange(int l, int r)
{
	l += element_count;
	r += element_count;
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
