#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
#define ll long long
const ll mod = 1e9;

class SegmentTree
{
private:
	vector<ll> tree;
	size_t element_count;
public:
	SegmentTree(const vector<ll>& elements)
	{
		element_count = elements.size();
		tree = vector<ll>(element_count * 2);
		copy(elements.begin(), elements.end(), tree.begin() + element_count);
		for (size_t i = element_count - 1; i >= 1; i--)
		{
			tree[i] = tree[i * 2] + tree[i * 2 + 1];
			tree[i] %= mod;
		}
	}
	void IncrementElement(int position, ll ammount = 1)
	{
		position += element_count;
		tree[position] += ammount;
		tree[position] %= mod;
		for (int i = position / 2; i >= 1; i /= 2)
		{
			tree[i] = tree[i * 2] + tree[i * 2 + 1];
			tree[i] %= mod;
		}
	}
	ll Query(int l, int r)
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

			sum %= mod;
			l /= 2;
			r /= 2;
		}
		return sum;
	}
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
	map<int, vector<int>, greater<int>> elements_position_map;
	vector<pair<int,int>> elements(n);
	for (size_t i = 0; i < n; i++)
	{
		int element;
		cin >> element;
		elements_position_map[element].push_back(i);
	}

	auto tree_0_1 = SegmentTree(vector<ll>(n, 0));
	auto tree_greater_sum = SegmentTree(vector<ll>(n, 0));

	ll solution = 0;

	for (auto& kvp: elements_position_map)
	{
		vector<int> temp(kvp.second.size());
		int i = 0;
		for (int original_position: kvp.second)
		{
			ll tuples_starting_from_current = tree_greater_sum.Query(original_position, n);
			int count_greater_on_right = tree_0_1.Query(original_position, n);
			temp[i++] = count_greater_on_right;

			solution += tuples_starting_from_current;
			solution %= mod;
		}

		i = 0;
		for (int original_position : kvp.second)
		{
			tree_0_1.IncrementElement(original_position, 1);
			tree_greater_sum.IncrementElement(original_position, temp[i++]);
		}
	}
	cout << solution << "\n";
	return 0;
}