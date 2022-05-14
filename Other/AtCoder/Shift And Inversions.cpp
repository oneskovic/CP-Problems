#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

class SegmentTree
{
public:
	SegmentTree(const vector<int>& elements);
	void update_element(int position, int new_value);
	int sum_query(int l, int r);
private:
	vector<int> tree;
	int element_cnt;
};

/// <summary>
/// Count the number of elements larger than the element at position i, on the interval [0,i)
/// </summary>
vector<int> prefix_inversions(vector<pair<int, int>> elements)
{
	int n = elements.size();
	sort(elements.begin(), elements.end(), greater<pair<int, int>>());
	auto tree = SegmentTree(vector<int>(n));
	vector<int> prefix_invs(n);
	for (int i = 0; i < n; i++)
	{
		int original_pos = elements[i].second;
		tree.update_element(original_pos, 1);
		prefix_invs[original_pos] = tree.sum_query(0, original_pos);
	}
	return prefix_invs;
}

/// <summary>
/// Count the number of elements smaller than the element at position i, on the interval (i,n)
/// </summary>
vector<int> suffix_inversions(vector<pair<int, int>> elements)
{
	int n = elements.size();
	sort(elements.begin(), elements.end());
	auto tree = SegmentTree(vector<int>(n));
	vector<int> suffix_inversions(n);
	for (int i = 0; i < n; i++)
	{
		int original_pos = elements[i].second;
		tree.update_element(original_pos, 1);
		suffix_inversions[original_pos] = tree.sum_query(original_pos + 1, n);
	}
	return suffix_inversions;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<pair<int, int>> elements(n);
	for (int i = 0; i < n; i++)
	{
		cin >> elements[i].first;
		elements[i].second = i;
	}
	auto prefix_invs = prefix_inversions(elements);
	auto suffix_invs = suffix_inversions(elements);
	
	ll inversion_cnt = 0;
	for (int x: prefix_invs)
		inversion_cnt += x;
	
	auto tree_elements_sorted_left = SegmentTree(vector<int>(n,1));
	auto tree_elements_sorted_right = SegmentTree(vector<int>(n, 0));

	for (int i = 0; i < n; i++)
	{
		cout << inversion_cnt << "\n";
		// Remove the first element
		inversion_cnt -= suffix_invs[i];
		// Add it to the back
		// Add the inversions in the "second part of the array"
		inversion_cnt += prefix_invs[i]; 
		tree_elements_sorted_left.update_element(elements[i].first, 0);
		// Add the inversions in the "leftover part of the array"
		inversion_cnt += tree_elements_sorted_left.sum_query(elements[i].first, n);
		
		inversion_cnt -= tree_elements_sorted_right.sum_query(0, elements[i].first);
		tree_elements_sorted_right.update_element(elements[i].first, 1);
	}

	return 0;
}

SegmentTree::SegmentTree(const vector<int>& elements)
{
	element_cnt = elements.size();
	tree = vector<int>(2 * element_cnt);
	copy(elements.begin(), elements.end(), tree.begin() + element_cnt);
	for (int i = element_cnt - 1; i > 0; i--)
		tree[i] = tree[2 * i] + tree[2 * i + 1];
}

void SegmentTree::update_element(int position, int new_value)
{
	position += element_cnt;
	tree[position] = new_value;
	for (int i = position / 2; i > 0; i /= 2)
		tree[i] = tree[2 * i] + tree[2 * i + 1];

}

int SegmentTree::sum_query(int l, int r)
{
	l += element_cnt;
	r += element_cnt;
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
