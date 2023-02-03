#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
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
		map<int, int> prefix_diff_cnt;
		string s; cin >> s;
		int current_prefix = 0;
		prefix_diff_cnt[0] = 1;
		for (int i = 0; i < s.size(); i++)
		{
			int x = s[i] - '0';
			current_prefix += x;
			prefix_diff_cnt[current_prefix - (i + 1)]++;
		}
		ll solution = 0;
		for (auto kvp : prefix_diff_cnt)
			solution += (ll)kvp.second * (kvp.second - 1) / 2;
		
		cout << solution << endl;
	}
	return 0;
}