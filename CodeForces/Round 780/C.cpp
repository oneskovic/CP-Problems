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
		string s; cin >> s;
		int n = s.size();

		vector<int> a(30);
		vector<bool> exists(30, false);
		int prev_dp = 0;
		int current_dp = 0;
		for (int i = 0; i < n; i++)
		{
			int val = s[i] - 'a';
			if (!exists[val])
			{
				current_dp = prev_dp + 1;
				a[val] = prev_dp - i - 1;
				exists[val] = 1;
			}
			else
			{
				current_dp = min(i + a[val], prev_dp + 1);
				a[val] = min(a[val], prev_dp - i - 1);
			}
			prev_dp = current_dp;
		}
		cout << current_dp << "\n";
	}

	return 0;
}