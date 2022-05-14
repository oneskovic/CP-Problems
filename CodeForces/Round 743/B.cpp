#include <algorithm>
#include <iostream>
#include <vector>
#include <limits.h>
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

		vector<int> position_of_number_a(2 * n + 1, INT_MAX);
		for (int i = 0; i < n; i++)
		{
			cin >> a[i];
			position_of_number_a[a[i]] = i;
		}
		for (int i = 0; i < n; i++)
			cin >> b[i];
		
		vector<int> prefix_min(2 * n + 1);
		prefix_min[0] = position_of_number_a[0];
		for (int i = 1; i < 2*n+1; i++)
			prefix_min[i] = min(prefix_min[i - 1], position_of_number_a[i]);

		int solution = INT_MAX;
		for (int i = 0; i < n; i++)
		{
			int current_sol = i + prefix_min[b[i]];
			solution = min(current_sol, solution);
		}

		cout << solution << "\n";
	}

	return 0;
}
