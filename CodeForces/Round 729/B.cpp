#include <algorithm>
#include <limits.h>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>

using namespace std;
typedef long long ll;

bool is_in_set(ll n, ll a, ll b)
{
	if (a == 1)
	{
		return (n - a) % b == 0;
	}
	ll a_pow = 1;
	while (a_pow <= n)
	{
		if ((n - a_pow) % b == 0)
		{
			return true;
		}
		a_pow *= a;
	}
	return false;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_cnt; cin >> test_cnt;
	for (size_t i = 0; i < test_cnt; i++)
	{
		ll n, a, b;
		cin >> n >> a >> b;
		if (is_in_set(n, a, b))
			cout << "Yes\n";
		else
			cout << "No\n";
	}
	return 0;
}