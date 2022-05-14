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
		int n; cin >> n;
		vector<ll> elements(n);
		for (int i = 0; i < n; i++)
			cin >> elements[i];
		
		vector<ll> solution(n);
		if (n % 2 == 0)
		{
			for (int i = 0; i < n; i++)
			{
				if (i % 2 == 0)
					solution[i] = -elements[i + 1];
				else
					solution[i] = elements[i - 1];
			}
		}
		else
		{
			for (int i = 0; i < n-3; i++)
			{
				if (i % 2 == 0)
					solution[i] = -elements[i + 1];
				else
					solution[i] = elements[i - 1];
			}
			solution[n - 3] = -(elements[n - 2] * elements[n - 1]);
			solution[n - 2] = elements[n - 3] * (elements[n - 1]*2);
			solution[n - 1] = -elements[n - 2] * elements[n - 3];
		}
		for (ll i: solution)
		{
			cout << i << " ";
		}
		cout << "\n";
	}

	return 0;
}