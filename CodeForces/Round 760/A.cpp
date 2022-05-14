#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		vector<ll> v(7);
		for (int i = 0; i < 7; i++)
			cin >> v[i];
		bool done = false;
		for (int i = 0; i < 7 && !done; i++)
		{
			for (int j = i+1; j < 7 && !done; j++)
			{
				for (int k = j+1; k < 7 && !done; k++)
				{
					ll a = v[i], b = v[j], c = v[k];
					vector<ll> t({ a,b,c,a + b,a + c,b + c,a + b + c });
					sort(t.begin(), t.end());
					if (equal(t.begin(),t.end(),v.begin()))
					{
						cout << a << " " << b << " " << c << "\n";
						done = 1;
					}
				}
			}
		}
	}
	return 0;
}
