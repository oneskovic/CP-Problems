#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

class SegmentTree
{
public:
	SegmentTree(const vector<ll>& elements);
	SegmentTree();
	ll sum(int l, int r);
	void update_value(int position, ll new_value);
private:
	vector<ll> tree;
	int element_count;
};

vector<int> find_positions_when_sorted(const vector<ll>& elements)
{
	vector<pair<ll, int>> element_original_pos(elements.size());
	for (size_t i = 0; i < elements.size(); i++)
		element_original_pos[i] = { elements.at(i),i };
	
	sort(element_original_pos.begin(), element_original_pos.end());

	vector<int> positions_when_sorted(elements.size());
	for (size_t i = 0; i < elements.size(); i++)
	{
		int original_pos = element_original_pos[i].second;
		positions_when_sorted[original_pos] = i;
	}
	return positions_when_sorted;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, k; cin >> n >> k;
	vector<ll> elements(n);
	for (size_t i = 0; i < n; i++)
		cin >> elements[i];
	
	vector<SegmentTree> trees(k+1);
	for (size_t i = 0; i <= k; i++)
		trees[i] = SegmentTree(vector<ll>(n));
	
	vector<int> position_when_sorted = find_positions_when_sorted(elements);
	for (size_t i = 0; i < n; i++)
	{
		trees[0].update_value(position_when_sorted[i], 1);
		for (int sequence_len = 1; sequence_len <= k; sequence_len++)
		{
			// Number of possible increasing sequences of length sequence_len-1 before the current position
			ll sequences_to_continue = trees[sequence_len - 1].sum(0, position_when_sorted[i]);
			trees[sequence_len].update_value(position_when_sorted[i], sequences_to_continue);
		}
	}
	cout << trees[k].sum(0, n);

	return 0;
}

SegmentTree::SegmentTree(const vector<ll>& elements)
{
	element_count = elements.size();
	tree = vector<ll>(element_count * 2);
	copy(elements.begin(), elements.end(), tree.begin() + element_count);

	for (int i = element_count-1; i > 0; i--)
		tree[i] = tree[2 * i] + tree[2 * i + 1];
}

SegmentTree::SegmentTree()
{
}

ll SegmentTree::sum(int l, int r)
{
	l += element_count;
	r += element_count;
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

void SegmentTree::update_value(int position, ll new_value)
{
	position += element_count;
	tree[position] = new_value;
	for (int i = position/2; i > 0; i/=2)
		tree[i] = tree[2 * i] + tree[2 * i + 1];
}
