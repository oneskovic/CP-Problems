#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		vector<int> elements(n);
		iota(elements.begin(), elements.end(), 1);
		for (int i = 0; i < n/2; i++)
			swap(elements[i], elements[n - i - 1]);
		if (n%2 == 1)
			swap(elements[0], elements[n / 2]);
		
		for (int element : elements)
			cout << element << " ";
		cout << "\n";
	}
	return 0;
}