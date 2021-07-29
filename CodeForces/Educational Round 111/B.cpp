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
		int n, a, b; cin >> n >> a >> b;
		string s; cin >> s;
		vector<int> s_vec;
		char prev_chr = 'a';
		for (int i = 0; i < s.size(); i++)
		{
			if (prev_chr == s[i])
			{
				continue;
			}
			else
			{
				s_vec.push_back(s[i] - '0');
				prev_chr = s[i];
			}
		}
		int cnt1 = count(s_vec.begin(), s_vec.end(), 1);
		int cnt0 = count(s_vec.begin(), s_vec.end(), 0);
		ll solution = a * n;
		if (b < 0)
		{
			int min_delete = min(cnt1, cnt0) + 1;
			solution += b * min_delete;
		}
		else
		{
			solution += n * b;
		}

		cout << solution << "\n";
	}
	return 0;
}