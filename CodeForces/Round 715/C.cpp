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
	for (size_t i = 0; i < n; i++)
	{
		cin >> elements[i];
	}
	sort(elements.begin(), elements.end());


	ll sol = LLONG_MAX;
	vector<ll> best;
	do
	{
		ll current_sum = 0;
		ll current_min = elements[0], current_max = elements[0];
		for (int i = 0; i < n; i++)
		{
			current_min = min(current_min, elements[i]);
			current_max = max(current_max, elements[i]);
			current_sum += current_max - current_min;
		}
		if (current_sum < sol)
		{
			best = elements;
			sol = current_sum;
		}
	} while (next_permutation(elements.begin(),elements.end()));

	sol = LLONG_MAX;
	for (int i = 0; i < n; i++)
	{
		ll current_sum = 0;
		int l = i, r = i;
		
		while (l > 0 && r < n - 1)
		{
			current_sum += elements[r] - elements[l];
			if (l == 0 || r == n - 1)
			{
				if (l > 0)
				{
					l--;
				}
				if (r < n - 1)
				{
					r++;
				}
			}
			else
			{
				ll option1 = elements[r] - elements[l - 1];
				ll option2 = elements[r + 1] - elements[l];
				if (option1 < option2)
					l--;
				else
					r++;
			}
		}
		current_sum += elements[r] - elements[l];
		sol = min(sol, current_sum);
	}
	cout << sol;

	return 0;
}