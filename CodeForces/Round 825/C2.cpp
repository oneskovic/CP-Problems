#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;

#include <vector>
#include <algorithm>
using namespace std;
#define ll long long
class SegmentTree
{
public:
	SegmentTree(const vector<ll>& elements);
	void update(int position, ll new_value);
	ll sum_query(int l, int r);
private:
	int element_count;
	vector<ll> tree;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<int> v(n);
	vector<vector<int>> diff_map(n + 5, vector<int>());
	set<int> bad_positions;
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
		int d = v[i] - (i + 1);
		if (d < 0)
		{
			diff_map[-d].push_back(i);
			bad_positions.insert(i);
		}
	}

	vector<int> first_blocked_by_pos(n+1,-1);
	vector<int> last_blocked_by_pos(n+1,-1);
	vector<int> blocked_by_index(n, -1);
	vector<ll> second_solution(n);
	vector<ll> first_solution(n);

	ll solution = 0;
	int offset = 0;
	for (int i = 0; i < n; i++)
	{
		int r = n;
		if (!bad_positions.empty())
			r = *bad_positions.begin();

		if (first_blocked_by_pos[r] == -1)
			first_blocked_by_pos[r] = i;
		last_blocked_by_pos[r] = i;
		blocked_by_index[i] = r;

		int second_r = n;
		if (bad_positions.size() >= 2)
			second_r = *(++bad_positions.begin());
		second_solution[i] = second_r - i;

		solution += r - i;
		first_solution[i] = r - i;
		offset++;
		for (int pos : diff_map[offset])
			bad_positions.erase(pos);

	}

	auto tree_first = SegmentTree(first_solution);
	auto tree_second = SegmentTree(second_solution);

	int query_cnt; cin >> query_cnt;
	while (query_cnt--)
	{
		int pos, new_val;
		cin >> pos >> new_val;
		pos--;
		if (new_val >= v[pos])
		{
			int delta = new_val - v[pos];
			int r = last_blocked_by_pos[pos];
			if (r == -1 || delta == 0)
			{
				cout << solution << "\n";
				continue;
			}
			int l = max(r - delta+1, first_blocked_by_pos[pos]);
			ll new_sol = solution - tree_first.sum_query(l, r + 1) + tree_second.sum_query(l, r + 1);
			cout << new_sol << "\n";
		}
		else
		{
			auto it = lower_bound(blocked_by_index.begin(), blocked_by_index.end(), pos);
			int l = it - blocked_by_index.begin();
			int r = pos - new_val;
			if (new_val - pos - 1 >= 0 || l > r)
			{
				cout << solution << "\n";
				continue;
			}

			ll len = pos - l;
			ll cnt = r - l;
			ll add = (cnt + 1) * len - cnt * (cnt + 1) / 2;
			ll new_sol = solution - tree_first.sum_query(l, r + 1) + add;
			cout << new_sol << "\n";
		}
	}
	return 0;
}

SegmentTree::SegmentTree(const vector<ll>& elements)
{
	element_count = elements.size();
	tree = vector<ll>(element_count * 2);
	copy(elements.begin(), elements.end(), tree.begin() + element_count);
	for (int i = element_count - 1; i > 0; i--)
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

void SegmentTree::update(int position, ll new_value)
{
	position += element_count;
	tree[position] = new_value;
	for (int i = position / 2; i > 0; i /= 2)
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

ll SegmentTree::sum_query(int l, int r)
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
