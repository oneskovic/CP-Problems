#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

class SegmentTreeGCD
{
public:
	SegmentTreeGCD(const vector<ll>& elements);
	ll Query(int l, int r);
private:
	ll gcd(ll a, ll b);
	vector<ll> tree;
	int element_count;
};
class SegmentTreeMin
{
public:
	SegmentTreeMin(const vector<ll>& elements);
	/// <summary>
	/// Returns a pair<ll,ll> : The minimum value and the number of times it appears in the interval [l,r) 
	/// </summary>
	pair<ll, ll> Query(int l, int r);
private:
	vector<ll> minimum_tree, count_tree;
	int element_count;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<ll> elements(n);
	for (size_t i = 0; i < n; i++)
		cin >> elements[i];
	auto min_tree = SegmentTreeMin(elements);
	auto gcd_tree = SegmentTreeGCD(elements);

	int query_count; cin >> query_count;
	for (size_t i = 0; i < query_count; i++)
	{
		int l, r; cin >> l >> r;
		l--; r--;
		auto query_answer = min_tree.Query(l, r + 1);
		ll min_in_segment = query_answer.first;
		ll min_count = query_answer.second;
		ll gcd_in_segment = gcd_tree.Query(l, r + 1);
		ll not_eaten = 0;
		if (min_in_segment == gcd_in_segment)
			not_eaten = min_count;
		cout << r - l + 1 - not_eaten << "\n";
	}
	return 0;
}

SegmentTreeGCD::SegmentTreeGCD(const vector<ll>& elements)
{
	ll g = gcd(2 * 2 * 3 * 3 * 5 * 7, 2 * 3 * 7 * 19);
	element_count = elements.size();
	tree = vector<ll>(2 * element_count);
	copy(elements.begin(), elements.end(), tree.begin() + element_count);
	for (int i = element_count - 1; i > 0; i--)
		tree[i] = gcd(tree[i * 2], tree[i * 2 + 1]);
}

ll SegmentTreeGCD::Query(int l, int r)
{
	l += element_count;
	r += element_count;
	ll result = -1;
	while (l < r)
	{
		if (l % 2 == 1)
			result = (result == -1 ? tree[l++] : gcd(result, tree[l++]));
		
		if (r % 2 == 1)
			result = (result == -1 ? tree[--r] : gcd(result, tree[--r]));
		
		l /= 2;
		r /= 2;
	}
	return result;
}

ll SegmentTreeGCD::gcd(ll a, ll b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

SegmentTreeMin::SegmentTreeMin(const vector<ll>& elements)
{
	element_count = elements.size();
	count_tree = vector<ll>(2 * element_count);
	minimum_tree = vector<ll>(2 * element_count);
	copy(elements.begin(), elements.end(), minimum_tree.begin() + element_count);
	fill(count_tree.begin() + element_count, count_tree.end(), 1);

	for (int i = element_count - 1; i > 0; i--)
	{
		if (minimum_tree[2 * i] == minimum_tree[2 * i + 1])
		{
			count_tree[i] = count_tree[2 * i] + count_tree[2 * i + 1];
			minimum_tree[i] = minimum_tree[2 * i];
		}
		else
		{
			if (minimum_tree[2 * i] < minimum_tree[2 * i + 1])
			{
				minimum_tree[i] = minimum_tree[2 * i];
				count_tree[i] = count_tree[2 * i];
			}
			else
			{
				minimum_tree[i] = minimum_tree[2 * i + 1];
				count_tree[i] = count_tree[2 * i + 1];
			}
		}
	}
}

pair<ll, ll> SegmentTreeMin::Query(int l, int r)
{
	ll min_value = LLONG_MAX;
	ll min_count = 0;
	l += element_count;
	r += element_count;
	while (l < r)
	{
		if (l % 2 == 1)
		{
			ll value_in_node = minimum_tree[l];
			ll count_in_node = count_tree[l];
			if (value_in_node == min_value)
			{
				min_count += count_in_node;
			}
			else if (value_in_node < min_value)
			{
				min_value = value_in_node;
				min_count = count_in_node;
			}
			l++;
		}
		if (r % 2 == 1)
		{
			r--;
			ll value_in_node = minimum_tree[r];
			ll count_in_node = count_tree[r];
			if (value_in_node == min_value)
			{
				min_count += count_in_node;
			}
			else if (value_in_node < min_value)
			{
				min_value = value_in_node;
				min_count = count_in_node;
			}
		}
		l /= 2;
		r /= 2;
	}

	return pair<ll, ll>(min_value, min_count);
}
