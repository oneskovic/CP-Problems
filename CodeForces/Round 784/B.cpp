#include <algorithm>
#include <iostream>
#include <vector>
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
		vector<int> element_cnt(n + 1);
		for (int i = 0; i < n; i++)
		{
			int x; cin >> x;
			element_cnt[x]++;
		}
		bool found = false;
		for (int i = 0; i <= n && !found; i++)
		{
			if (element_cnt[i] >= 3)
			{
				cout << i << "\n";
				found = 1;
			}
		}
		if (!found)
		{
			cout << "-1\n";
		}
	}

	return 0;
}
