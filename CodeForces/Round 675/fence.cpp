#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int main()
{
	int q; cin >> q;
	for (size_t i = 0; i < q; i++)
	{
		long long a, b, c;
		cin >> a >> b >> c;
		cout << a + b + c - 1 << "\n";
	}
	return 0;
}