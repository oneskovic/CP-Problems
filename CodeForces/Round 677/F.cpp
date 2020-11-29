#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define ll long long

int main()
{
	int num_rows, num_cols, mod; cin >> num_rows >> num_cols >> mod;
	auto elements = vector<vector<int>>(num_rows);
	for (size_t i = 0; i < num_rows; i++)
	{
		elements[i] = vector<int>(num_cols);
		for (size_t j = 0; j < num_cols; j++)
			cin >> elements[i][j];
	}

	vector<vector<vector<vector<int>>>> dp(num_rows);
	int max_count = num_cols / 2;

	for (size_t row = 0; row < num_rows; row++)
	{
		dp[row] = vector<vector<vector<int>>>(mod);
		for (size_t remainder = 0; remainder < mod; remainder++)
		{
			dp[row][remainder] = vector<vector<int>>(num_cols);
			for (size_t i = 0; i < num_cols; i++)
			{
				dp[row][remainder][i] = vector<int>(max_count + 1);
				dp[row][remainder][i][0] = 0;
			}
		}
	}

	for (size_t row = 0; row < num_rows; row++)
	{
		for (size_t remainder = 0; remainder < mod; remainder++)
		{
			for (size_t count = 1; count <= max_count; count++)
				dp[row][remainder][0][count] = elements[row][0] % mod == remainder ? elements[row][0] : 0;
		}
	}

	// dp[i][j][k][l] -> dp[row][rem][pos][count]
	for (size_t row = 0; row < num_rows; row++)
	{
		for (size_t position = 0; position < num_cols; position++)
		{
			if (position == 0 && row == 0)
				continue;
			for (size_t remainder = 0; remainder < mod; remainder++)
			{
				for (size_t count = 0; count <= max_count; count++)
				{
					ll take_number = 0; 
					if (count > 0)
					{
						ll remainder_if_taken = (remainder - elements[row][position] % mod + mod) % mod;

						if (position == 0)
							take_number = *max_element(dp[row - 1][remainder_if_taken][num_cols - 1].begin(), dp[row - 1][remainder_if_taken][num_cols - 1].end());
						else
							take_number = dp[row][remainder_if_taken][position - 1][count - 1];

						if (take_number == 0 && remainder_if_taken > 0)
							take_number = 0;
						else
							take_number += elements[row][position];
					}
					ll do_not_take_number;
					if (position == 0)
						do_not_take_number = *max_element(dp[row - 1][remainder][num_cols - 1].begin(), dp[row - 1][remainder][num_cols - 1].end());
					else
					{
						do_not_take_number = dp[row][remainder][position - 1][count];
					}
					dp[row][remainder][position][count] = max(take_number, do_not_take_number);
				}
			}
		}
	}
	
	cout << dp[num_rows-1][0][num_cols-1][max_count];
	return 0;
}