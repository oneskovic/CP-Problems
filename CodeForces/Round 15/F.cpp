#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

class SegmentTree
{
public:
	SegmentTree(const vector<ll>& elements);
	void range_add(int l, int r, ll delta);
	ll query(int pos);
private:
	void update(int pos, ll delta);
	vector<ll> tree;
	int element_cnt;
};

void add(vector<ll>& x, int r, int ammount = 1)
{
	for (int i = 0; i < r; i++)
	{
		x[i] += ammount;
		x[i] %= mod;
	}
}

struct portal
{
	int src, dest;
	bool is_active;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<int> points; points.reserve(n);
	vector<portal> portals(n);
	points.push_back(0);

	for (int i = 0; i < n; i++)
	{
		int src, dest, state; cin >> src >> dest >> state;
		portals[i] = {src,dest,(bool)state};
		points.push_back(src);
		points.push_back(dest);
	}
	map<int, int> point_map;
	sort(points.begin(), points.end());
	points.erase(unique(points.begin(), points.end()), points.end());
	points.push_back(points.back() + 1);
	vector<int> portal_dest(points.size(), -1);
	vector<bool> is_active(points.size());

	for (int i = 0; i < points.size(); i++)
		point_map[points[i]] = i;
	for (int i = 0; i < portals.size(); i++)
	{
		int src_index = point_map[portals[i].src];
		int dest_index = point_map[portals[i].dest];
		portal_dest[src_index] = dest_index;
		is_active[src_index] = portals[i].is_active;
	}

	auto tree = SegmentTree(vector<ll>(points.size()));
	ll sol = 0;
	for (int i = 1; i < points.size(); i++)
	{
		tree.range_add(0, i, points[i] - points[i - 1]);
		if (portal_dest[i] != -1)
		{
			tree.range_add(i, i + 1, tree.query(portal_dest[i]));
			tree.range_add(0, i, tree.query(i));
		}
		if (is_active[i])
		{
			sol += tree.query(i);
			sol %= mod;
		}
		sol += points[i] - points[i - 1];
		sol %= mod;
	}
	cout << (sol % mod + mod) % mod;
	return 0;
}

SegmentTree::SegmentTree(const vector<ll>& elements)
{
	element_cnt = elements.size();
	vector<ll> diffs(element_cnt);
	diffs[0] = elements[0];
	for (int i = 1; i < element_cnt; i++)
		diffs[i] = elements[i] - elements[i - 1];

	tree = vector<ll>(2 * element_cnt);
	copy(diffs.begin(), diffs.end(), tree.begin() + element_cnt);
	for (int i = element_cnt - 1; i > 0; i--)
		tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

void SegmentTree::range_add(int l, int r, ll delta)
{
	if (r < element_cnt)
		update(r, -delta);
	update(l, delta);
}

ll SegmentTree::query(int pos)
{
	int l = element_cnt, r = pos + element_cnt + 1;
	ll sol = 0;
	while (l < r)
	{
		if (l % 2 == 1)
		{
			sol += tree[l++];
			sol %= mod;
		}

		if (r % 2 == 1)
		{
			sol += tree[--r];
			sol %= mod;
		}

		l /= 2;
		r /= 2;
	}
	return sol % mod;
}

void SegmentTree::update(int pos, ll delta)
{
	pos += element_cnt;
	tree[pos] += delta;
	tree[pos] %= mod;
	for (int i = pos / 2; i > 0; i /= 2)
		tree[i] = (tree[2 * i] + tree[2 * i + 1]) % mod;
}
