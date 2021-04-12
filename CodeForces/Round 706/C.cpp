#include <algorithm>
#include <iostream>	
#include <vector>
#include <iomanip>
#include <math.h> 
using namespace std;
#define ll long long
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_count; cin >> test_count;
	for (int test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		vector<ll> x_axis, y_axis;
		x_axis.reserve(n); y_axis.reserve(n);

		for (size_t i = 0; i < 2*n; i++)
		{
			ll x, y;
			cin >> x >> y;
			if (x == 0)
			{
				y_axis.push_back(abs(y));
			}
			else
			{
				x_axis.push_back(abs(x));
			}
		}
		sort(x_axis.begin(), x_axis.end());
		sort(y_axis.begin(), y_axis.end());

		double solution = 0;
		for (size_t i = 0; i < n; i++)
		{
			ll x = x_axis[i];
			ll y = y_axis[i];
			solution += sqrt(x * x + y * y);
		}
		
		cout << setprecision(10) << fixed << solution << "\n";
	}
	return 0;
}