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
		vector<int> a(n), b(n);
		for (int i = 0; i < n; i++)
			cin >> a[i];
		for (int i = 0; i < n; i++)
			cin >> b[i];
		vector<pair<int,int>> positions_larger, positions_smaller;
		int sum_larger = 0, sum_smaller = 0;
		for (int i = 0; i < n; i++)
		{
			if (a[i] > b[i])
			{
				positions_larger.push_back({ i,a[i] - b[i] });
				sum_larger += a[i] - b[i];
			}
			else if (a[i] < b[i])
			{
				positions_smaller.push_back({ i,b[i] - a[i] });
				sum_smaller += b[i] - a[i];
			}
		}
		if (sum_larger == sum_smaller)
		{
			cout << sum_larger << "\n";
			int i = 0, j = 0;
			while (i < positions_larger.size() && j < positions_smaller.size())
			{
				int iterations = min(positions_larger[i].second, positions_smaller[j].second);
				for (int t = 0; t < iterations; t++)
				{
					cout << positions_larger[i].first+1 << " " << positions_smaller[j].first+1 << "\n";
				}
				positions_smaller[j].second -= iterations;
				positions_larger[i].second -= iterations;
				if (positions_smaller[j].second == 0)
					j++;
				if (positions_larger[i].second == 0)
					i++;
			}
		}
		else
		{
			cout << "-1\n";
		}


	}

	return 0;
}