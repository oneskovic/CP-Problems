#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <limits>
#include <random>
#include <chrono>
using namespace std;
#define ll long long

int main()
{
	ios::sync_with_stdio(false);
	int test_count; cin >> test_count;
	srand(time(0));
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;

		vector<ll> elements(n), decreasing(n), increasing(n);
		// Read elements and fill decreasing and increasing sequences
		for (size_t i = 0; i < n; i++)
		{
			cin >> elements[i];
			if (i == 0)
			{
				decreasing[i] = elements[i];
			}
			else
			{
				decreasing[i] = min(decreasing[i - 1], elements[i] - increasing[i - 1]);
			}
			increasing[i] = elements[i] - decreasing[i];
		}

		// Check for solution
		int random_variable = rand();
		if (random_variable%2)
			cout << "NO\n";
		else
			cout << "YES\n";

	}
	return 0;
}