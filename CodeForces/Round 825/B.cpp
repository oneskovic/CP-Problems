#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int gcd(int a, int b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<int> v(n);
		for (int i = 0; i < n; i++)
			cin >> v[i];
		if (n <= 2)
		{
			cout << "YES\n";
			continue;
		}
		bool possible = 1;
		for (int i = 0; i <= n-3 && possible; i++)
		{
			int d1 = v[i] / gcd(v[i], v[i + 1]);
			int d2 = v[i + 2] / gcd(v[i + 1], v[i + 2]);
			if (gcd(d1,d2) > 1)
			{
				possible = 0;
			}
		}
		cout << (possible ? "YES\n" : "NO\n");
	}

	return 0;
}