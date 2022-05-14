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
		int sol = 1;
		if (n <= 1399)
			sol = 4;
		else if (n <= 1599)
			sol = 3;
		else if (n <= 1899)
			sol = 2;
		cout << "Division " << sol << "\n";
	}

	return 0;
}
