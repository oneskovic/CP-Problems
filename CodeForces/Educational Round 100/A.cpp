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
		ll a, b, c;
		cin >> a >> b >> c;
		ll min_div = min(min(a / 3, b / 3),c/3);
		a -= 3 * min_div;
		b -= 3 * min_div;
		c -= 3 * min_div;
		if (a == 0 && b == 0 && c == 0)
		{
			cout << "YES\n";
		}
		else if (min(min(a,b),c) == 1 && (a + b + c - 3 == 6))
		{
			cout << "YES\n";
		}
		else if (min(min(a,b),c) == 2 && (a + b + c - 6 == 12 || a + b + c - 3 == 6))
		{
			cout << "YES\n";
		}
		else
			cout << "NO\n";
	}
	return 0;
}
