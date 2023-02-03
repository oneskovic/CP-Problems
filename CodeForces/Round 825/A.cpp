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
		vector<int> a(n);
		vector<int> b(n);
		int excess_ones = 0;
		int lacking_ones = 0;
		for (int i = 0; i < n; i++)
			cin >> a[i];
		for (int i = 0; i < n; i++)
		{
			cin >> b[i];
			if (b[i] == 1 && a[i] == 0)
				lacking_ones++;
			if (b[i] == 0 && a[i] == 1)
				excess_ones++;
		}
		if (lacking_ones == 0 && excess_ones == 0)
		{
			cout << "0\n";
		}
		else
		{
			if (min(lacking_ones,excess_ones) == 0)
			{
				cout << lacking_ones + excess_ones << "\n";
			}
			else
			{
				int ops = abs(lacking_ones - excess_ones) + 1;
				cout << ops << "\n";
			}
		}

	}

	return 0;
}