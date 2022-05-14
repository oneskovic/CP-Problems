#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

int solve(vector<ll>& s, int l, int r)
{
	if (r - l + 1 <= 2)
		return 0;
	if (s[l] != s[l+1])
		return solve(s, l + 1, r);
	if (s[r] != s[r-1])
		return solve(s, l, r - 1);
	if (s[l] == s[l+1])
	{
		s[l + 1] = s[l + 2] + 1;
		s[l + 2]++;
		return solve(s, l + 1, r) + 1;
	}
	else if (s[r] == s[r-1])
	{
		s[r - 1] = s[r - 2] + 1;
		s[r - 2]++;
		return solve(s, l, r - 1) + 1;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<ll> s(n);
		for (int i = 0; i < n; i++)
			cin >> s[i];
		cout << solve(s, 0, n - 1) << "\n";
	}

	return 0;
}