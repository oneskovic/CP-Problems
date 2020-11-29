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
		int n, m;
		cin >> n >> m;
		int count_zeros = 0, count_negative = 0;
		vector<vector<int>> elements(n);
		for (size_t i = 0; i < n; i++)
		{
			elements[i] = vector<int>(m);
			for (size_t j = 0; j < m; j++)
			{
				int element; cin >> element;
				elements[i][j] = element;

				if (element == 0)
					count_zeros++;
				else if (element < 0)
					count_negative++;
			}
			if (count_negative % 2 == 1)
			{
				if (count_zeros > 0)
					count_negative = 0;
				else
					count_negative = 1;
			}
		}

		int min_element = INT_MAX;
		long long sum = 0;
		for (size_t row = 0; row < n; row++)
		{
			for (size_t col = 0; col < m; col++)
			{
				sum += abs(elements[row][col]);
				min_element = min(min_element, abs(elements[row][col]));
			}
		}
		if (count_negative == 1)
			sum -= 2*min_element;
		cout << sum << "\n";
	}
	return 0;
}