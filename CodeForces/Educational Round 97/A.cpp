#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long

int main()
{
	ios::sync_with_stdio(false);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		ll low, high; cin >> low >> high;
		double limit = (high + 1) / 2.0;
		if (low % (high + 1) < limit)
		{
			cout << "NO\n";
		}
		else
			cout << "YES\n";
	}
	return 0;
}