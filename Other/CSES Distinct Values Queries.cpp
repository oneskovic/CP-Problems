#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>
#include <map>
using namespace std;

class SegmentTree
{
public:
	SegmentTree(const vector<int>& elements);
	void update(int position, int value);
	int sum(int l, int r);
private:
	vector<int> tree;
	int element_cnt;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, q; cin >> n >> q;
	SegmentTree rightmost_position_tree = SegmentTree(vector<int>(n));

	vector<int> elements(n);
	for (int i = 0; i < n; i++)
		cin >> elements[i];
	
	vector<tuple<int, int, int>> queries(q); // right index first
	for (int i = 0; i < q; i++)
	{
		int l, r;
		cin >> l >> r;
		queries[i] = { r,l,i };
	}
	sort(queries.begin(), queries.end());

	map<int, int> rightmost_position;
	int j = 0;
	vector<int> solution(q);
	for (int i = 0; i < n; i++)
	{
		int element = elements[i];
		if (rightmost_position.find(element) != rightmost_position.end())
		{
			rightmost_position_tree.update(rightmost_position[element], 0);
		}
		rightmost_position[element] = i;
		rightmost_position_tree.update(i, 1);
		while(j < queries.size() && get<0>(queries[j])-1 == i)
		{
			int l = get<1>(queries[j]);
			int r = get<0>(queries[j]);
			int query_index = get<2>(queries[j]);
			solution[query_index] = rightmost_position_tree.sum(l - 1, r);
			j++;
		}
	}
	for (int i : solution)
	{
		cout << i << "\n";
	}
	return 0;
}

SegmentTree::SegmentTree(const vector<int>& elements)
{
	element_cnt = elements.size();
	tree = vector<int>(2 * element_cnt);
	copy(elements.begin(), elements.end(), tree.begin() + element_cnt);
	for (int i = element_cnt - 1; i > 0; i--)
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

void SegmentTree::update(int position, int value)
{
	position += element_cnt;
	tree[position] = value;
	for (int i = position / 2; i > 0; i /= 2)
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

int SegmentTree::sum(int l, int r)
{
	int sum = 0;
	l += element_cnt; r += element_cnt;
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
