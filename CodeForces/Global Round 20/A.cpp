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
		int cnt_larger_than_2 = 0;
		int cnt_2 = 0;
		for (int i = 0; i < n; i++)
		{
			int x; cin >> x;
			if (x > 2)
			{
				cnt_larger_than_2++;
			}
			if (x == 2)
			{
				cnt_2++;
			}
		}
		if (cnt_larger_than_1 > 0)
		{
			cout << "errorgorn\n";
		}
		else
			cout << "maomao90\n";
	}

	return 0;
}