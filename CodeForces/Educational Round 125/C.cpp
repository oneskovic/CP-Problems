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
		int cnt_ops = 0;
		int curr_len = 0;
		bool found_one = false;
		for (int i = 0; i < n; i++)
		{
			if (i < n-1 && s[i] == '(' && !found_one)
			{
				cnt_ops++;
				curr_len = 0;
				i++;
			}
			else
			{
				curr_len++;
				if (s[i] == ')')
				{
					if (found_one)
					{
						curr_len = 0;
						cnt_ops++;
						found_one = false;
					}
					else
					{
						found_one = true;
					}
				}
			}
		}
		cout << cnt_ops << " " << curr_len << "\n";
	}
	return 0;
}