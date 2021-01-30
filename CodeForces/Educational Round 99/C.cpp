#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int test_count; cin >> test_count;
	for (size_t test_no	= 0; test_no < test_count; test_no++)
	{
		int a, b; cin >> a >> b;
		cout << a - 1 << " " << b << "\n";
	}
	return 0;
}