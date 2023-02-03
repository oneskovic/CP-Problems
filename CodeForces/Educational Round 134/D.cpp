#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

struct group
{
	vector<int> arr_a, arr_b;
};

bool check_group(const group& g)
{
	return g.arr_a.size() == g.arr_b.size();
}

pair<group, group> split_group(const group& g, int mask)
{
	group g1, g2;
	int n = g.arr_a.size();
	for (int i = 0; i < n; i++)
	{
		if (g.arr_a[i] & mask)
			g2.arr_a.push_back(g.arr_a[i]);
		else
			g1.arr_a.push_back(g.arr_a[i]);

		if (g.arr_b[i] & mask)
			g1.arr_b.push_back(g.arr_b[i]);
		else
			g2.arr_b.push_back(g.arr_b[i]);
	}
	return { g1, g2 };
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		group start_group;
		start_group.arr_a = vector<int>(n);
		start_group.arr_b = vector<int>(n);
		for (int i = 0; i < n; i++)
			cin >> start_group.arr_a[i];
		for (int i = 0; i < n; i++)
			cin >> start_group.arr_b[i];

		vector<group> groups = { start_group };
		int mask = 1 << 30;
		int result = 0;
		while (mask > 0)
		{
			vector<group> new_groups;
			bool success = 1;
			for (group& g : groups)
			{
				auto res = split_group(g, mask);
				group g1 = res.first;
				group g2 = res.second;
				if (!check_group(g1) || !check_group(g2))
				{
					success = 0;
					break;
				}
				else
				{
					if (!g1.arr_a.empty())
						new_groups.push_back(g1);
					if (!g2.arr_a.empty())
						new_groups.push_back(g2);
				}
			}
			if (success)
			{
				result |= mask;
				groups = new_groups;
			}
			mask >>= 1;
		}
		cout << result << "\n";
	}

	return 0;
}
