#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<ll> elements(n);
	for (int i = 0; i < n; i++)
	{
		cin >> elements[i];
	}

	ll solution = 0;
	for (int l = 0; l < n; l+=2)
	{
		ll sum = elements[l];
		ll remaining_on_left = elements[l];
		for (int r = l+1; r < n; r+=2)
		{
			ll delta = elements[r - 1] - elements[r];
			if (r == l+1)
			{
				delta = -elements[r];
			}
			sum += delta;
			if (sum <= remaining_on_left)
			{
				if (r != l + 1)
				{
					solution++;
				}
				solution += min(remaining_on_left, abs(delta));
				remaining_on_left = sum;
			}
			if (sum < 0)
				break;
		}
	}
	cout << solution << "\n";

	return 0;
}
