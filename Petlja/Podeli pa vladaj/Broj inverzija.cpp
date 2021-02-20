#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
#define ll long long

// Performs the merge-sort algorithm while counting inversions on the interval [l,r)
ll merge_sort(int l, int r, vector<int>& elements, vector<int>& auxiliary)
{
	if (l+1==r)
		return 0;
	
	ll mid = (l + r) / 2;
	ll inversion_count = merge_sort(l, mid, elements, auxiliary) + merge_sort(mid, r, elements, auxiliary);
	int i = l, j = mid;
	int position_to_place = l;
	while (i < mid || j < r)
	{
		if (i < mid && (j == r || elements[i] <= elements[j]))
		{
			auxiliary[position_to_place++] = elements[i++];
		}
		else
		{
			auxiliary[position_to_place++] = elements[j++];
			inversion_count += (mid - i);
		}
	}
	copy(auxiliary.begin() + l, auxiliary.begin() + r, elements.begin() + l);
	return inversion_count;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
	vector<int> elements(n), auxiliary(n);
	for (size_t i = 0; i < n; i++)
		cin >> elements[i];
	cout << merge_sort(0, n, elements, auxiliary);
	return 0;
}