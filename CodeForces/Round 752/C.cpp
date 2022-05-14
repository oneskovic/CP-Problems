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
		vector<ll> elements(n);
		vector<ll> divisor_cnt(n);
		for (int i = 0; i < n; i++)
		{
			cin >> elements[i];
		}
		bool possible = true;
		for (int i = 0; i < min(n,30); i++)
		{
			bool divisible_by_all = true;
			for (int j = 2; j <= i+2; j++)
			{
				if (elements[i] % j != 0)
				{
					divisible_by_all = false;
					break;
				}
			}
			if (divisible_by_all)
				possible = false;
		}
		if (possible)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}