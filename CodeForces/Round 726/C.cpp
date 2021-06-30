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
		vector<int> elements(n);
		for (int i = 0; i < n; i++)
			cin >> elements[i];
		sort(elements.begin(), elements.end());
		int min_pos = -1;
		int min_diff = INT_MAX;
		for (int i = 0; i < n-1; i++)
		{
			int d = elements[i + 1] - elements[i];
			if (d <= min_diff)
			{
				min_diff = d;
				min_pos = i;
			}
		}
		cout << elements[min_pos] << " ";
		for (int i = min_pos+2; i < n; i++)
		{
			cout << elements[i] << " ";
		}
		for (int i = 0; i < min_pos; i++)
		{
			cout << elements[i] << " ";
		}
		cout << elements[min_pos + 1] << "\n";		
	}
	return 0;
}