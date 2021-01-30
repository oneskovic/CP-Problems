#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		int max_prefix_a = 0;
		int max_prefix_a_pos = -1;
		int current_prefix = 0;
		vector<int> a(n);
		for (size_t i = 0; i < n; i++)
		{
			cin >> a[i];
			current_prefix += a[i];
			if (current_prefix >= max_prefix_a)
			{
				max_prefix_a = current_prefix;
				max_prefix_a_pos = i;
			}
		}
		
		int m; cin >> m;
		int max_prefix_b = 0;
		int max_prefix_b_pos = -1;
		current_prefix = 0;
		vector<int> b(m);
		for (size_t i = 0; i < m; i++)
		{
			cin >> b[i];
			current_prefix += b[i];
			if (current_prefix >= max_prefix_b)
			{
				max_prefix_b = current_prefix;
				max_prefix_b_pos = i;
			}
		}

		cout << max_prefix_a + max_prefix_b << "\n";
	}
	return 0;
}