#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
#define ll long long

vector<ll> solve_for_matrix(const vector<string>& elements)
{
	int n = elements.size();
	vector<int> min_digit_y(10, INT_MAX), max_digit_y(10, INT_MIN);
	for (int digit = 0; digit <= 9; digit++)
	{
		for (int row = 0; row < n; row++)
		{
			for (int col = 0; col < n; col++)
			{
				if (elements[row][col]-'0' == digit)
				{
					min_digit_y[digit] = min(min_digit_y[digit], row);
					max_digit_y[digit] = max(max_digit_y[digit], row);
				}
			}
		}
	}

	vector<ll> solutions(10);
	for (int digit = 0; digit <= 9; digit++)
	{
		ll max_area = 0;
		for (int row = 0; row < n; row++)
		{
			int min_x = INT_MAX, max_x = INT_MIN;
			for (int col = 0; col < n; col++)
			{
				if (elements[row][col] - '0' == digit)
				{
					min_x = min(min_x, col);
					max_x = max(max_x, col);
				}
			}
			if (min_x == INT_MAX)
				continue;
			
			int max_y = max(row, n - 1 - row);
			ll area1 = abs(row * (min_x - max_x) + max_y * (max_x - min_x));

			int dy = max(max_digit_y[digit] - row, row - min_digit_y[digit]);
			int dx = max(max_x, n - 1 - min_x);
			ll area2 = abs(dy*dx);
			max_area = max(max_area,max(area1, area2));
		}
		solutions[digit] = max_area;
	}
	return solutions;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		vector<string> elements(n);
		for (size_t i = 0; i < n; i++)
			cin >> elements[i];

		auto solutions1 = solve_for_matrix(elements);

		auto rotated_elements = elements;
		for (size_t i = 0; i < n; i++)
			for (size_t j = 0; j < n; j++)	
				rotated_elements[j][i] = elements[i][j];
		auto solutions2 = solve_for_matrix(rotated_elements);
		
		for (size_t digit = 0; digit <= 9; digit++)
		{
			cout << max(solutions1[digit], solutions2[digit]) << " ";
		}
		cout << "\n";
	}
	return 0;
}