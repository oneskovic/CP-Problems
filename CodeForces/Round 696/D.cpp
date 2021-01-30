#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		vector<int> elements(n);
		for (size_t i = 0; i < n; i++)
			cin >> elements[i];

		vector<int> no_swap_left(n, -1), no_swap_right(n, -1);
		no_swap_left[0] = 0;
		for (size_t i = 1; i < n; i++)
		{
			int needed_to_clear = elements[i - 1] - no_swap_left[i - 1];
			if (needed_to_clear < 0)
				break;
			no_swap_left[i] = needed_to_clear;
		}

		no_swap_right[n - 1] = 0;
		for (int i = n-2; i >= 0; i--)
		{
			int needed_to_clear = elements[i + 1] - no_swap_right[i + 1];
			if (needed_to_clear < 0)
				break;
			no_swap_right[i] = needed_to_clear;
		}

		bool possible = false;
		if (no_swap_left.back() == elements.back() || no_swap_right.front() == elements.front())
		{
			possible = true;
		}
		
		// Try to swap every i and i+1
		for (size_t i = 0; i < n-1; i++)
		{
			bool left_ok = false;
			int new_no_swap_left1 = elements[i + 1] - no_swap_left[i];
			int new_no_swap_left2 = elements[i] - new_no_swap_left1;
			if ((i == n-2 && new_no_swap_left2 == 0) ||
				(i < n-2 && new_no_swap_left2 == elements[i+2]))
			{
				left_ok = true;
			}

			bool right_ok = false;
			int new_no_swap_right1 = elements[i] - no_swap_right[i + 1];
			int new_no_swap_right2 = elements[i + 1] - new_no_swap_right1;
			if ((i == 0 && new_no_swap_right2 == 0) ||
				(i > 0 && new_no_swap_right2 == elements[i-1]))
			{
				right_ok = true;
			}

			if (left_ok && right_ok)
			{
				possible = true;
				break;
			}
		}

		if (possible)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}