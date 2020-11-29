#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		cout << n << "\n";
		for (size_t i = 1; i <= n; i++)
			cout << i << " ";
		cout << "\n";
	}
	return 0;
}