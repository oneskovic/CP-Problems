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

		int cnt_zeros = 0;
		int cnt_ones = 0;
		for (int i = 0; i < n; i++)
		{
			if (s[i] == '0')
				cnt_zeros++;
			else
				cnt_ones++;
		}

		int longest_equal_str = 0;
		int current_len = 1;
		for (int i = 1; i < n; i++)
		{
			if (s[i] == s[i-1])
			{
				current_len++;
			}
			else
			{
				longest_equal_str = max(longest_equal_str, current_len);
				current_len = 1;
			}
		}
		longest_equal_str = max(longest_equal_str, current_len);

		ll sol1 = (ll)cnt_ones * cnt_zeros;
		ll sol2 = (ll)longest_equal_str * longest_equal_str;
		cout << max(sol1, sol2) << "\n";
	}

	return 0;
}