#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		string s; cin >> s;
		vector<bool> bits(n);
		for (int i = 0; i < n; i++)
		{
			if (s[i] == '1')
				bits[i] = 1;
		}

		vector<int> cost_to_zero(n);
		bool bit_to_skip = 0;
		if (bits[0] == 1)
		{
			cost_to_zero[0] = 1;
			bit_to_skip = 1;
		}
		for (int i = 1; i < n; i++)
		{
			cost_to_zero[i] = cost_to_zero[i - 1];
			if (bits[i] != bit_to_skip)
			{
				cost_to_zero[i]++;
				bit_to_skip = !bit_to_skip;
			}
		}

		vector<vector<int>> cost_to_suffix(2,vector<int>(n));
		if (bits.back() == 0)
			cost_to_suffix[1].back() = 1;
		else
			cost_to_suffix[0].back() = 1;
		for (int i = n - 2; i >= 0; i--)
		{
			if (bits[i] == 0)
			{
				cost_to_suffix[0][i] = cost_to_suffix[0][i + 1];
				cost_to_suffix[1][i] = cost_to_suffix[0][i + 1] + 1;
			}
			else
			{
				cost_to_suffix[1][i] = cost_to_suffix[1][i + 1];
				cost_to_suffix[0][i] = cost_to_suffix[1][i + 1] + 1;
			}
		}
		int opt1 = cost_to_zero.back();
		int opt2 = cost_to_suffix[1][0];
		int solution = min(opt1, opt2);
		for (int i = 0; i < n-1; i++)
		{
			int opt = cost_to_zero[i] + cost_to_suffix[1][i+1];
			solution = min(solution, opt);
		}
		cout << solution << "\n";
	}

	return 0;
}