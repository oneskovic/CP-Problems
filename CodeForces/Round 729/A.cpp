#include <algorithm>
#include <limits.h>
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
		int cnt_even = 0, cnt_odd = 0;
		for (int i = 0; i < 2*n; i++)
		{
			int element; cin >> element;
			if (element % 2 == 0)
				cnt_even++;			
			else
				cnt_odd++;
		}
		if (cnt_even == cnt_odd)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}