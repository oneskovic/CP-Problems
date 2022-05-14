#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
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
		string s; cin >> s;
		vector<int> prefix_a(n), prefix_b(n);
		prefix_a[0] = (s[0] == 'a');
		prefix_b[0] = (s[0] == 'b');
		for (int i = 1; i < n; i++)
		{
			prefix_a[i] = prefix_a[i - 1];
			prefix_b[i] = prefix_b[i - 1];
			if (s[i] == 'a')
				prefix_a[i]++;
			else
				prefix_b[i]++;
		}
		bool found = false;
		for (int l = 0; l < n && !found; l++)
		{
			for (int r = l+1; r < n && !found; r++)
			{
				int cnt_a = (l == 0 ? prefix_a[r] : prefix_a[r] - prefix_a[l - 1]);
				int cnt_b = (l == 0 ? prefix_b[r] : prefix_b[r] - prefix_b[l - 1]);
				if (cnt_a == cnt_b)
				{
					cout << l + 1 << " " << r + 1 << "\n";
					found = 1;
				}
			}
		}
		if (!found)
		{
			cout << "-1 -1 \n";
		}
	}

	return 0;
}