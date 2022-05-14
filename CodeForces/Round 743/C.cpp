#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<int> in_degree(n);
		vector<vector<int>> g(n, vector<int>());
		for (int i = 0; i < n; i++)
		{
			int k; cin >> k;
			for (int j = 0; j < k; j++)
			{
				int a; cin >> a;
				a--;
				g[a].push_back(i);
				in_degree[i]++;
			}
		}
		set<int> nodes_deg_zero;
		for (int i = 0; i < n; i++)
		{
			if (in_degree[i] == 0)
				nodes_deg_zero.insert(i);
		}

		if (nodes_deg_zero.size() == 0)
		{
			cout << "-1\n";
			continue;
		}
		else
		{
			int solution = 1;
			int current_node = *nodes_deg_zero.begin();
			int solved_nodes = nodes_deg_zero.size();
			while (!nodes_deg_zero.empty())
			{
				for (int dependent_node: g[current_node])
				{
					in_degree[dependent_node]--;
					if (in_degree[dependent_node] == 0)
					{
						nodes_deg_zero.insert(dependent_node);
						solved_nodes++;
					}
				}
				int prev_node = current_node;
				auto it = nodes_deg_zero.upper_bound(current_node);
				if (it == nodes_deg_zero.end())
				{
					current_node = *nodes_deg_zero.begin();
					if (nodes_deg_zero.size() > 1)
					{
						solution++;
					}
				}
				else
				{
					current_node = *it;
				}
				nodes_deg_zero.erase(prev_node);
			}
			if (solved_nodes == n)
				cout << solution << "\n";
			else
				cout << "-1\n";
		}
	}

	return 0;
}
