#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		ll a, b, c, d;
		cin >> a >> b >> c >> d;
		ll lhs = a * d, rhs = b * c;
		if (lhs == rhs)
		{
			cout << "0\n";
		}
		else
		{
			ll g = gcd(lhs, rhs);
			lhs /= g; rhs /= g;
			if (lhs == 1 || rhs == 1 || lhs == 0 || rhs == 0)
				cout << "1\n";
			else
				cout << "2\n";
		}
	}
	return 0;
}