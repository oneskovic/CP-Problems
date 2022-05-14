#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <chrono>
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

class MinSumSegmentTree
{
public:
	MinSumSegmentTree(const vector<ll>& v);
	ll sum_query(int l, int r);
	void update(int pos, ll new_value);
private:
	vector<ll> tree, min_value, subtree_size;
	int element_cnt;
	pair<int, int> combine(int l, int r);
};

struct query
{
	int l, r;
	ll x;
	int index;
};

ll evaluete_query(query q, const vector<int>& function_type, const vector<ll>& constants)
{
	ll solution = 0;
	ll y = q.x;
	for (int i = q.l; i <= q.r; i++)
	{
		if (function_type[i] == 0)
		{
			y = min(y, constants[i]);
		}
		else if (function_type[i] == 1)
		{
			y = max(y, constants[i]);
		}
		else
		{
			y = y + constants[i];
		}
		solution += y;
	}
	return solution;
}

vector<ll> bruteforce(const vector<int>& function_type, const vector<ll>& constants, vector<query>& queries)
{
	int n = function_type.size();
	vector<ll> solutions(queries.size());
	for (int q = 0; q < queries.size(); q++)
	{
		solutions[q] = evaluete_query(queries[q], function_type, constants);
	}
	return solutions;
}

vector<ll> solve_all_sum(const vector<ll>& constants, vector<query>& queries)
{
	int n = constants.size();
	vector<ll> solutions(queries.size());
	vector<ll> prefix_sums(n);
	prefix_sums[0] = constants[0];
	for (int i = 1; i < n; i++)
	{
		prefix_sums[i] = prefix_sums[i - 1] + constants[i];
	}
	
	SegmentTree tree(prefix_sums);
	for (int q = 0; q < queries.size(); q++)
	{
		int l = queries[q].l, r = queries[q].r;
		int d = r - l + 1;
		ll to_subtract = (l == 0 ? 0 : d * prefix_sums[l - 1]);
		solutions[q] = tree.sum_query(queries[q].l, queries[q].r+1) - to_subtract + d*queries[q].x;
	}

	return solutions;
}

vector<ll> solve_all_min(const vector<ll>& constants, vector<query>& queries)
{
	int n = constants.size();
	vector<ll> solutions(queries.size());

	MinSumSegmentTree tree(constants);
	for (int q = 0; q < queries.size(); q++)
	{
		int l = queries[q].l, r = queries[q].r;
		if (queries[q].x < constants[l])
		{
			tree.update(l, queries[q].x);
		}
		solutions[q] = tree.sum_query(queries[q].l, queries[q].r);
		tree.update(l, constants[l]);
	}

	return solutions;
}

void test()
{
	int n = rand() % 5 + 1;
	vector<int> function_type(n,0);
	vector<ll> constants(n);

	for (int i = 0; i < n; i++)
		constants[i] = rand()%10-5;

	int query_cnt = rand()%10;
	vector<query> queries(query_cnt);
	for (int i = 0; i < query_cnt; i++)
	{
		queries[i].l = rand() % n;
		queries[i].r = rand() % n;
		if (queries[i].l > queries[i].r)
		{
			swap(queries[i].l, queries[i].r);
		}
		queries[i].x = rand() % 10-5;
		queries[i].index = i;
	}

	auto sol1 = bruteforce(function_type, constants, queries);
	auto sol2 = solve_all_min(constants, queries);
	if (sol1 != sol2)
	{
		cout << "wa\n";
		solve_all_min(constants, queries);
	}
	else
		cout << "ok\n";
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

	auto sols = bruteforce(function_type, constants, queries);
	for (auto x: sols)
	{
		cout << x << "\n";
	}
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

MinSumSegmentTree::MinSumSegmentTree(const vector<ll>& v)
{
	element_cnt = v.size();
	tree = vector<ll>(2 * element_cnt);
	min_value = vector<ll>(2 * element_cnt);
	subtree_size = vector<ll>(2 * element_cnt, 1);
	copy(v.begin(), v.end(), tree.begin() + element_cnt);
	copy(v.begin(), v.end(), min_value.begin() + element_cnt);
	for (int i = element_cnt - 1; i >= 0; i--)
		subtree_size[i] = subtree_size[2 * i] + subtree_size[2 * i + 1];

	for (int i = element_cnt - 1; i >= 0; i--)
	{
		auto res = combine(2 * i, 2 * i + 1);
		tree[i] = res.first;
		min_value[i] = res.second;
	}
}

ll MinSumSegmentTree::sum_query(int l, int r)
{
	l += element_cnt;
	r += element_cnt;
	ll min_left = LLONG_MAX;
	ll sum_left = 0;
	ll size_left = 0;
	ll min_right = LLONG_MAX;
	ll sum_right = 0;
	ll size_right = 0;
	while (l < r)
	{
		if (l % 2 == 1)
		{
			if (min_value[l] > min_left)
			{
				sum_left += subtree_size[l] * min_left;
			}
			else
			{
				sum_left += tree[l];
				min_left = min_value[l];
			}
			size_left += subtree_size[l];
			l++;
		}
		if (r % 2 == 1)
		{
			r--;
			if (min_value[r] > min_right)
			{
				sum_right += subtree_size[r] * min_right;
			}
			else
			{
				sum_right += tree[r];
				min_right = min_value[r];
			}
			size_right += subtree_size[r];
		}
		l /= 2;
		r /= 2;
	}
	
	ll sum = sum_left;
	if (min_right > min_left)
	{
		sum += size_right * min_left;
	}
	else
		sum += sum_right;

	return sum;
}

void MinSumSegmentTree::update(int pos, ll new_value)
{
	pos += element_cnt;
	tree[pos] = new_value;
	min_value[pos] = new_value;
	pos /= 2;
	while (pos > 0)
	{
		auto res = combine(2 * pos, 2 * pos + 1);
		tree[pos] = res.first;
		min_value[pos] = res.second;
		pos /= 2;
	}
}

pair<int,int> MinSumSegmentTree::combine(int l, int r)
{
	ll res = tree[l];
	if (min_value[l] < min_value[r])
	{
		res += subtree_size[r] * min_value[l];
	}
	else
	{
		res += tree[r];
	}
	ll res_min = min(min_value[l], min_value[r]);
	return { res, res_min };
}
