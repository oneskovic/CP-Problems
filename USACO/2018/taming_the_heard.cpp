#include <bits/stdc++.h>
using namespace std;

int difference_cnt(const vector<int>& elements, int l, int r)
{
	int diff = 0;
	for (int i = 1; i <= r-l; i++)
	{
		diff += (elements[l+i-1] != i);
	}
	return diff + (elements[r] != 0);
}

void print_vec(const vector<vector<int>>& v)
{
    for(auto row: v)
    {
        for(int i : row)
        {
            if(i < INT_MAX)
                cout << i << " ";
            else
                cout << "- ";
        }
        cout << "\n";
    }
    cout << "\n";
}

int main()
{
    freopen("taming.in", "r", stdin);
	freopen("taming.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<int> elements(n);
	for (size_t i = 0; i < n; i++)
		cin >> elements[i];

	vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
	dp[0][0] = (elements[0] != 0);
	for (int i = 1; i < n; i++)
		dp[0][i] = dp[0][i - 1] + (elements[i] != i);
    cout << dp[0].back() << "\n";
	for (int i = 1; i < n; i++)
		dp[1][i] = dp[0][i - 1] + (elements[i] != 0);

    int min_val = INT_MAX;
    for (int pos = 1; pos < n; pos++)
    {
        int actual_diff = dp[1][pos];
        for (int i = 1; i < n - pos; i++)
        {
            actual_diff += (elements[pos + i] != i);
        }
        min_val = min(min_val, actual_diff);
    }
    cout << min_val << "\n";

    //print_vec(dp);
	for (int zero_cnt = 2; zero_cnt < n; zero_cnt++)
	{
		for (int pos = zero_cnt; pos < n; pos++)
		{
			min_val = INT_MAX;
			for (int prev_pos = zero_cnt-1; prev_pos < pos; prev_pos++)
			{
				min_val = min(min_val, difference_cnt(elements, prev_pos+1, pos) + dp[zero_cnt-1][prev_pos]);
			}
			dp[zero_cnt][pos] = min_val;
		}

        //print_vec(dp);
		min_val = INT_MAX;
		for (int pos = zero_cnt; pos < n; pos++)
		{
			int actual_diff = dp[zero_cnt][pos];
			for (int i = 1; i < n - pos; i++)
			{
				actual_diff += (elements[pos + i] != i);
			}
			min_val = min(min_val, actual_diff);
		}
		cout << min_val << "\n";
	}
	return 0;
}
