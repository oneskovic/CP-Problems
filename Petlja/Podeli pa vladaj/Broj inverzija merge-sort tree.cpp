#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
#define ll long long
class MergeSortTree
{
public:
	MergeSortTree(const vector<int>& elements);
	/// <summary>
	/// Finds the number of elements greater than x in the interval [l,r)
	/// </summary>
	int Query(int l, int r, int x);
private:
	int element_count;
	vector<vector<int>> tree;
};

MergeSortTree::MergeSortTree(const vector<int>& elements)
{
	element_count = elements.size();
	tree = vector<vector<int>>(element_count * 2);
	for (size_t i = 0; i < element_count; i++)
		tree[i + element_count] = { elements[i] };
	
	for (int i = element_count - 1; i > 0; i--)
	{
		tree[i] = vector<int>(tree[i * 2].size() + tree[i * 2 + 1].size());
		merge(tree[i * 2].begin(), tree[i * 2].end(), 
			tree[i * 2 + 1].begin(), tree[i * 2 + 1].end(),
			tree[i].begin());
	}
}

int MergeSortTree::Query(int l, int r, int x)
{
	l += element_count; r += element_count;
	int count = 0;
	while (l < r)
	{
		if (l % 2 == 1)
		{
			count += tree[l].end() - upper_bound(tree[l].begin(), tree[l].end(), x);
			l++;
		}
		if (r % 2 == 1)
		{
			r--;
			count += tree[r].end() - upper_bound(tree[r].begin(), tree[r].end(), x);
		}
		l /= 2; r /= 2;
	}
	return count;
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
	vector<int> elements(n);
	for (size_t i = 0; i < n; i++)
		cin >> elements[i];
	auto mst = MergeSortTree(elements);
	ll inversion_count = 0;

	for (size_t i = 1; i < elements.size(); i++)
	{
		inversion_count += mst.Query(0, i, elements[i]);
	}

	cout << inversion_count;
	return 0;
}