#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		int digit = n % 10;
		int prev_count = (digit - 1) * 10;
		int digits_count = 0;
		while (n % 10 > 0)
		{
			n /= 10;
			digits_count++;
		}
		digits_count = digits_count * (digits_count + 1) / 2;
		
		cout << digits_count + prev_count << "\n";
	}
	return 0;
}