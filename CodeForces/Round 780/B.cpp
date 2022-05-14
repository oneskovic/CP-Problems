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
		
		sort(elements.begin(), elements.end(), greater<ll>());
		if (n == 1)
		{
			if (elements[0] > 1)
				cout << "NO\n";
			else
				cout << "YES\n";
		}
		else
		{

			if (elements[0] - elements[1] >= 2)
				cout << "NO\n";
			else
				cout << "YES\n";
		}
	}

	return 0;
}