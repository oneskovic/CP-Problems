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
		ll n, k; cin >> n >> k;
		ll solution = 0;
		ll pow_of_2 = 1;
		ll next_pow_of_2 = 2;
		ll remaining = n;
		while (next_pow_of_2 - pow_of_2 <= k && remaining > next_pow_of_2)
		{
			solution++;
			pow_of_2 *= 2;
			next_pow_of_2 *= 2;
		}
		remaining -= pow_of_2;
		solution += remaining / k;
		solution += (remaining % k > 0);
		cout << solution << "\n";
	}
	return 0;
}