#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define ll long long

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		set<int> lenghts;
		int n; cin >> n;
		vector<int> points(n);
		for (size_t i = 0; i < n; i++)
			cin >> points[i];
		
		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = i; j < n; j++)
			{
				if (i == j)
					continue;
				int distance = abs(points[i] - points[j]);
				if (distance != 0)
				{
					lenghts.insert(distance);
				}
			}
		}
		cout << lenghts.size() << "\n";
	}

	return 0;
}