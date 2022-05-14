#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;

class SegmentTree
{
public:
	SegmentTree(const vector<ll>& v);
	ll sum_query(int l, int r);
	void update(int pos, ll new_value);
private:
	vector<ll> tree;
	int element_cnt;
};


struct query
{
	int l, r;
	ll x;
	int index;
};

struct function_attributes
{
	ll val_smallest, val_largest;
	ll constant_mid;
};

struct function_interval_piece
{
	bool is_start;
	ll x;
	int index;
};

bool operator < (const query& lhs, const query& rhs)
{
	return lhs.x < rhs.x;
}

bool operator < (const function_interval_piece& lhs, const function_interval_piece& rhs)
{
	return lhs.x < rhs.x;
}

void add_intervals(const function_attributes& attr, vector<function_interval_piece>& intervals, int index, ll min_x, ll max_x)
{
	function_interval_piece left, right;

	// assume the function has 3 parts
	// x + attr.constant_mid = attr.val_smallest
	// x = attr.val_smallest - attr.constant_mid
	left = { true, attr.val_smallest - attr.constant_mid, index };
	right = { false, attr.val_largest - attr.constant_mid, index };

	if (min_x + attr.constant_mid == attr.val_smallest) // unbounded left
	{
		left = { true, min_x - 1, index };
	}

	if (max_x + attr.constant_mid == attr.val_largest) // unbounded right
	{
		right = { false, max_x + 1, index };
	}
	
	if (attr.val_smallest != attr.val_largest)
	{
		intervals.push_back(left);
		intervals.push_back(right);
	}
}

vector<ll> solve(const vector<int>& function_type, const vector<ll>& constants, vector<query> queries)
{
	// 0 = min, 1 = max, 2 = add
	int n = function_type.size();
	sort(queries.begin(), queries.end());
	vector<function_attributes> func_attr(n);
	ll min_x = queries.front().x;
	ll max_x = queries.back().x;

	ll y_min = min_x;
	ll y_max = max_x;
	ll to_add = 0;
	vector<function_interval_piece> intervals; intervals.reserve(n);
	for (int i = 0; i < n; i++)
	{
		if (function_type[i] == 0)
		{
			ll arg = constants[i];
			y_min = min(y_min, arg);
			y_max = min(y_max, arg);
		}
		else if (function_type[i] == 1)
		{
			ll arg = constants[i];
			y_min = max(y_min, arg);
			y_max = max(y_max, arg);
		}
		else
		{
			to_add += constants[i];
			y_min += constants[i];
			y_max += constants[i];
		}
		func_attr[i].val_smallest = y_min;
		func_attr[i].val_largest = y_max;
		func_attr[i].constant_mid = to_add;
		add_intervals(func_attr[i], intervals, i, min_x, max_x);
	}
	sort(intervals.begin(), intervals.end());

	vector<ll> start_constants(n);
	for (int i = 0; i < n; i++)
		start_constants[i] = func_attr[i].val_smallest;
	
	SegmentTree constant_tree = SegmentTree(start_constants);
	SegmentTree contains_x_tree = SegmentTree(vector<ll>(n));

	vector<ll> solutions(queries.size());
	int interval_index = 0;
	for (int query_index = 0; query_index < queries.size(); query_index++)
	{
		while (interval_index < intervals.size() && intervals[interval_index].x <= queries[query_index].x)
		{
			int index = intervals[interval_index].index;
			if (intervals[interval_index].is_start)
			{
				constant_tree.update(index, func_attr[index].constant_mid);
				contains_x_tree.update(index, 1);
			}
			else
			{
				constant_tree.update(index, func_attr[index].val_largest);
				contains_x_tree.update(index, 0);
			}
			interval_index++;
		}
		query q = queries[query_index];
		ll x_cnt = contains_x_tree.sum_query(q.l, q.r + 1);
		ll solution = constant_tree.sum_query(q.l, q.r + 1) + x_cnt*q.x;
		solutions[q.index] = solution;
	}

	return solutions;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<int> function_type(n);
	vector<ll> constants(n);
	for (int i = 0; i < n; i++)
	{
		cin >> function_type[i];
		function_type[i]--;
	}

	for (int i = 0; i < n; i++)
		cin >> constants[i];
	
	int query_cnt; cin >> query_cnt;
	vector<query> queries(query_cnt);
	for (int i = 0; i < query_cnt; i++)
	{
		cin >> queries[i].l >> queries[i].r >> queries[i].x;
		queries[i].l--;
		queries[i].r--;
		queries[i].index = i;
	}

	auto sols = solve(function_type, constants, queries);

	for (auto x: sols)
	{
		cout << x << " ";
	}
	cout << "\n";

	return 0;
}


SegmentTree::SegmentTree(const vector<ll>& elements)
{
	element_cnt = elements.size();
	tree = vector<ll>(2 * element_cnt);
	copy(elements.begin(), elements.end(), tree.begin() + element_cnt);
	for (int i = element_cnt - 1; i >= 0; i--)
	{
		tree[i] = tree[2 * i] + tree[2 * i + 1];
	}
}

ll SegmentTree::sum_query(int l, int r)
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

void SegmentTree::update(int pos, ll new_value)
{
	pos += element_cnt;
	tree[pos] = new_value;
	pos /= 2;
	while (pos > 0)
	{
		tree[pos] = tree[2 * pos] + tree[2 * pos + 1];
		pos /= 2;
	}
}