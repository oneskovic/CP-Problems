#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <chrono>
using namespace std;
#define ll long long
/// <summary>
/// A merge sort tree
/// </summary>
class SegmentTree {
public:
	SegmentTree(const vector<int>& elements);
	/// <summary>
	/// Returns the number of elements greater than q in [l,r)
	/// </summary>
	ll Query(int l, int r, int q);
private:
	int element_count;
	vector<vector<int>> tree;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
	vector<int> elements(n);
	for (size_t i = 0; i < n; i++)
		cin >> elements[i];

	unordered_map<int, int> previous_position;
	vector<int> next_position(n);
	// Start from the right and fill the next_position vector
	for (int i = n - 1; i >= 0; i--)
	{
		int current_element = elements[i];
		if (previous_position.find(current_element) != previous_position.end())
			next_position[i] = previous_position[current_element];
		else
			next_position[i] = INT_MAX;
		previous_position[current_element] = i;
	}

	auto next_position_tree = SegmentTree(next_position);
	
	int q; cin >> q;
	for (size_t i = 0; i < q; i++)
	{
		int l, r; cin >> l >> r;
		cout << next_position_tree.Query(l-1, r, r-1) << "\n";
	}

	return 0;
}

SegmentTree::SegmentTree(const vector<int>& elements)
{
	element_count = elements.size();
	tree = vector<vector<int>>(element_count * 2);
	for (size_t i = element_count; i < element_count*2; i++)
		tree[i] = vector<int>{ elements[i - element_count] };
	for (int i = element_count - 1; i > 0; i--)
	{
		tree[i] = vector<int>(tree[i * 2].size() + tree[i * 2 + 1].size());
		merge(tree[i * 2].begin(), tree[i * 2].end(), tree[i * 2 + 1].begin(), tree[i * 2 + 1].end(), tree[i].begin());
	}
}

ll SegmentTree::Query(int l, int r, int q)
{
	l += element_count; r += element_count;
	ll count = 0;
	while (l < r)
	{
		if (l % 2 == 1)
		{
			count += tree[l].end() - upper_bound(tree[l].begin(), tree[l].end(), q);
			l++;
		}
		if (r % 2 == 1)
		{
			r--;
			count += tree[r].end() - upper_bound(tree[r].begin(), tree[r].end(), q);
		}
		l /= 2; r /= 2;
	}
	return count;
}
