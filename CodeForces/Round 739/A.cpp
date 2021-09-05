#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

bool check(int n)
{
	if (n % 3 == 0)
		return false;
	if (n % 10 == 3)
		return false;
	return true;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int k; cin >> k;
		int n = 1;
		while (k > 0)
		{
			if (check(n))
				k--;
			n++;
		}
		cout << --n << "\n";
	}

	return 0;
}