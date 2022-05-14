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
		if (n % 2 == 0)
		{
			cout << "YES\n";
		}
		else
		{
			if (adjacent_find(elements.begin(), elements.end(), greater_equal<ll>()) == elements.end())
				cout << "NO\n";
			else
				cout << "YES\n";
		}
	}
	return 0;
}