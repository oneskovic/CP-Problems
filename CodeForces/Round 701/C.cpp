#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
#define ll long long

ll condition_switch_b(ll x)
{
	ll l = 0, r = x;
	while (l+1 < r)
	{
		ll b = (l + r) / 2;
		bool condition = x / (b + 1) >= b;
		if (condition)
			l = b;
		else
			r = b;
	}

	return l;
}

int main()
{
	int test_count; cin >> test_count;
	for (size_t i = 0; i < test_count; i++)
	{
		ll x, y; cin >> x >> y;
		ll csb = condition_switch_b(x);
		ll t = min(csb, y); t--;
		ll solution_number = (t*(t+1))/2;
		/*for (int bi = 2; bi <= csb && bi <= y; bi++)
		{
			solution_number += bi - 1;
		}*/
		for (int bi = csb + 1; x / (bi+1) > 0 && bi <= y; bi++)
			solution_number += x / (bi+1);
		cout << solution_number << endl;
	}

	
	return 0;
}