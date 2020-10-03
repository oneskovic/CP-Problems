#include <vector>
#include <algorithm>
using namespace std;
#define ll long long
/// <summary>
/// A simple sum query segment tree
/// </summary>
class SegmentTree
{
public:
	SegmentTree(const vector<ll>& elements);
	void Modify(int position, ll new_value);
	ll Query(int l, int r);
private:
	int element_count;
	vector<ll> tree;
};

SegmentTree::SegmentTree(const vector<ll>& elements)
{
	element_count = elements.size();
	tree = vector<ll>(element_count * 2);
	copy(elements.begin(), elements.end(), tree.begin() + element_count);
	for (int i = element_count-1; i > 0; i--)
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

void SegmentTree::Modify(int position, ll new_value)
{
	position += element_count;
	tree[position] = new_value;
	for (int i = position / 2; i > 0; i--)
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

ll SegmentTree::Query(int l, int r)
{
	l += element_count; r += element_count;
	ll sum = 0;
	while (l < r)
	{
		if (l % 2 == 1)
			sum += tree[l++];
		if (r % 2 == 1)
			sum += tree[--r];
		
		l /= 2; r /= 2;
	}
	return sum;
}
