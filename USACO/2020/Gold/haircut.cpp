#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

class SegmentTree 
{
public:
	SegmentTree(const vector<int>& elements);
	void update(int position, int value);
	ll sum(int l, int r);
private:
	vector<int> tree;
	int element_cnt;
};

int main()
{
	// Make a segment tree on the array [1,1,1,...1] representing elements strictly larger
	// than the current "length" being considered. Add elements in sorted order.
	// For example when considering the cut length
	// 1, set position of all elements that equal 0 to 0 and find the sum [0,position of element] 
	// when considering the length 2, set position of all elements = 1 and find the sum.

	freopen("haircut.in", "r", stdin);
	freopen("haircut.out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
	vector<vector<int>> value_position_map(n + 1, vector<int>());
	for (int i = 0; i < n; i++)
	{
		int element; cin >> element;
		value_position_map[element].push_back(i);
	}

	SegmentTree larger_elements_tree(vector<int>(n,1));
	cout << 0 << "\n";
	ll inversion_cnt = 0;
	for (int current_value = 0; current_value < n-1; current_value++)
	{
		for (int pos: value_position_map[current_value])
		{
			larger_elements_tree.update(pos, 0);
		}
		for (int pos : value_position_map[current_value])
		{
			inversion_cnt += larger_elements_tree.sum(0, pos);
		}
		cout << inversion_cnt << "\n";
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

void SegmentTree::update(int position, int value)
{
	position += element_cnt;
	tree[position] = value;
	for (int i = position/2; i > 0; i/=2)
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

ll SegmentTree::sum(int l, int r)
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
