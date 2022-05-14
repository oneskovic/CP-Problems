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
		int a, b; cin >> a >> b;
		if (a == 0)
		{
			cout << "1\n";
		}
		else
		{
			cout << a + 2 * b + 1 << "\n";
		}
	}

	return 0;
}