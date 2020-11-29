#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);

	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		unsigned long long a, b;
		cin >> a >> b;
		unsigned long long mask = 1;
		for (size_t i = 0; i < 64; i++)
		{
			if ((a & mask) && (b&mask))
			{
				a ^= mask;
				b ^= mask;
			}
			mask *= 2;
		}
		cout << a + b << "\n";
	}
	return 0;
}
