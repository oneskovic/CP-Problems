#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long
 
int main()
{
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		ll p, q; cin >> p >> q;
		ll q_start = q;
		ll x = p;
		ll max_x = p % x == 0 && x % q != 0 ? x : 1;
 
		ll divisor_candidate = 2;
		while (divisor_candidate * divisor_candidate <= q)
		{
			x = p;
			while (q % divisor_candidate == 0 && x % divisor_candidate == 0)
			{
				x /= divisor_candidate;
				if (p % x == 0 && x % q_start != 0)
				{
					max_x = max(max_x, x);
				}
			}
			while (q % divisor_candidate == 0)
			{
				q /= divisor_candidate;
			}
			divisor_candidate++;
		}
		if (q > 1)
		{
			x = p;
			if (x % q == 0)
			{
				x /= q;
				if (p % x == 0 && x % q_start != 0)
				{
					max_x = max(max_x, x);
				}
			}
		}
 
		if (max_x == 70946929)
		{
			cout << p << "," << q_start << "\n";
		}
		else
			cout << max_x << "\n";
	}
	
	return 0;
}