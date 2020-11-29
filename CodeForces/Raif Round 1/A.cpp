#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long
int main()
{
	int no_tests; cin >> no_tests;
	for (size_t i = 0; i < no_tests; i++)
	{
		ll x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		ll dx = abs(x1 - x2);
		ll dy = abs(y1 - y2);
		if (dx == 0)
		{
			cout << dy;
		}
		else if (dy == 0)
		{
			cout << dx;
		}
		else
		{
			cout << dx + dy + 2;
		}
		cout << "\n";
	}
	return 0;
}