#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int a, b, c;
		cin >> a >> b >> c;

		ll pow_x = (a - c + 1) * 3;
		ll pow_y = (b - c + 1) * 2;

		ll x = pow((ll)2,pow_x), y = pow((ll)3,pow_y);
		ll g = pow((ll)10, c-1);
		cout << x*g << " " << y*g << "\n";
	}
	return 0;
}