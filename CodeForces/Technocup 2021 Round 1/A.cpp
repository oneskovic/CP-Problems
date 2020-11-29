#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long

int main()
{
	ios::sync_with_stdio(false);
	int no_tests; cin >> no_tests;
	for (size_t i = 0; i < no_tests; i++)
	{
		int n; cin >> n;
		vector<int> elements(n);
		for (size_t i = 0; i < n; i++)
			cin >> elements[i];
		vector<int> solutions(n);
		for (size_t i = 0; i < n/2; i++)
			solutions[i] = elements[n - i - 1] * -1;
		
		for (size_t i = n/2; i < n; i++)
			solutions[i] = elements[n - i - 1];
		
		for (int sol: solutions)
			cout << sol << " ";
		cout << "\n";
	}
	return 0;
}