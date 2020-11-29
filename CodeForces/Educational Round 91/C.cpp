#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;
#define ll long long

class SegmentTree
{
public:
	SegmentTree(const vector<ll>& elements);
	void Modify(int position, ll new_value);
	ll Query(int l, int r);
	int CheckLength(int len, ll min_value);
private:
	int element_count;
	vector<ll> tree;
};

SegmentTree::SegmentTree(const vector<ll>& elements)
{
	element_count = elements.size();
	tree = vector<ll>(element_count * 2);
	copy(elements.begin(), elements.end(), tree.begin() + element_count);
	for (int i = element_count - 1; i > 0; i--)
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

void SegmentTree::Modify(int position, ll new_value)
{
	position += element_count;
	tree[position] = new_value;
	for (int i = position / 2; i > 0; i /= 2)
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

int SegmentTree::CheckLength(int len, ll min_value)
{
	int l = 0, r = element_count;
	while (l + 1 < r)
	{
		int mid = (l + r) / 2;
		if (Query(mid, element_count) >= len)
			r = mid;
		else
			l = mid;
	}
	if (r != element_count)
		return r;
	return -1;
}



int main()
{
	int n, min_value; cin >> n >> min_value;
	vector<ll> elements(n);
	for (size_t i = 0; i < n; i++)
		cin >> elements[i];
	vector<ll> all_ones(n,1);
	auto remaining_elements = SegmentTree(all_ones);

	int remaining = n;
	int solution = 0;
	while (true)
	{
		int l = 1, r = remaining+1;
		while (r - l > 1)
		{
			int mid = (r - l) / 2;
			if (remaining_elements.CheckLength(mid, min_value) != -1)
				r = mid;
			else
				l = mid;
		}
		if (r == remaining+1)
		{
			break;
		}
		else
		{
			int min_length = r;
			int position = remaining_elements.CheckLength(min_length, min_value);
			for (size_t i = 0; i < min_length; i++)
			{
				remaining_elements.Modify(position + i, 0);
			}
			solution++;
		}
	}
	return 0;
}