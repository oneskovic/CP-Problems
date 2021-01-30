#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		int a = ceil(0.5 * (1 + sqrt(1 + 8 * n)));
		if (a * (a - 1) / 2 > n && a * (a - 1) / 2 - n < 2)
			a++;
		cout << a - 1 << "\n";
	}
	return 0;
}