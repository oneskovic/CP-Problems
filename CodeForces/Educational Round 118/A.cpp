#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

int digit_cnt(int x)
{
	int d = 0;
	while (x > 0)
	{
		x /= 10;
		d++;
	}
	return d;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		ll x1, zeros1;
		cin >> x1 >> zeros1;
		
		ll x2, zeros2;
		cin >> x2 >> zeros2;
		
		string solution = "";

		if (zeros1 < zeros2)
		{
			zeros2 -= zeros1;
			zeros1 = 0;
			for (int i = 0; i < min(zeros2,(ll)10); i++)
			{
				x2 *= 10;
			}
		}
		else
		{
			zeros1 -= zeros2;
			zeros2 = 0;
			for (int i = 0; i < min(zeros1, (ll)10); i++)
			{
				x1 *= 10;
			}
		}
		if (x1 < x2)
			solution = "<";
		else if (x1 == x2)
			solution = "=";
		else
			solution = ">";
		cout << solution << "\n";

	}

	return 0;
}