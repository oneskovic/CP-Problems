#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;
#define ll long long

class SegmentTree
{
private:
	vector<ll> tree;
	size_t element_count;
public:
	SegmentTree(const vector<ll>& elements);
	void Increment(int position, int increment = 1);
	ll SumRange(int l, int r);
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<ll> elements(n);
	for (size_t i = 0; i < n; i++)
		cin >> elements[i];

	// Count the number of elements that appear i times
	// Eg. tree[2] = the number of elements that appear 2 times
	auto tree = SegmentTree(vector<ll>(n + 1, 0));
	unordered_map<ll, int> appearance_count_right, appearance_count_left;
	for (size_t i = 1; i < n; i++)
		appearance_count_right[elements[i]]++;
	
	appearance_count_left[elements[0]]++;
	ll solution = 0;
	for (size_t j = 1; j < n; j++)
	{
		ll current_element = elements[j];
		// The number of elements that have appeared more times than the current element (n is the maximum number of appearances)
		solution += tree.SumRange(appearance_count_right[current_element]+1, n+1);

		appearance_count_right[current_element]--;
		appearance_count_left[current_element]++;
		tree.Increment(appearance_count_left[current_element]); // Add the current number of appearances to the tree
	}
	cout << solution << "\n";

	return 0;
}

SegmentTree::SegmentTree(const vector<ll>& elements)
{
	element_count = elements.size();
	tree = vector<ll>(2 * element_count);
	copy(elements.begin(), elements.end(), tree.begin() + element_count);
	for (int i = element_count-1; i >= 1; i--)
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

void SegmentTree::Increment(int position, int increment)
{
	position += element_count;
	tree[position] += increment;
	for (int i = position / 2; i >= 1; i /= 2)
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

ll SegmentTree::SumRange(int l, int r)
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
