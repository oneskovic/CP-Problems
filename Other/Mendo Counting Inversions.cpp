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

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<pair<int,int>> elements(n);
	for (int i = 0; i < n; i++)
	{
		cin >> elements[i].first;
		elements[i].second = i;
	}
	sort(elements.begin(), elements.end());
	auto tree = SegmentTree(vector<int>(n));
	ll sol = 0;
	for (int i = 0; i < n; i++)
	{
		int original_pos = elements[i].second;
		tree.update_element(original_pos, 1);
		sol += tree.sum_query(original_pos+1, n);
	}
	cout << sol << "\n";
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
	for (int i = position/2; i > 0; i/=2)
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
