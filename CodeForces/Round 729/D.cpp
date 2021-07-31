#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef long long ll;
const ll mod = 998244353;
struct operation
{
	bool type;
	int argument;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<operation> ops(n);
	for (int i = 0; i < n; i++)
	{
		char type; cin >> type;
		if (type == '-')
		{
			ops[i] = { 0,-1 };
		}
		else
		{
			ops[i] = { 1,-1 };
			cin >> ops[i].argument;
		}
	}
	
	ll solution = 0;
	for (int pos_to_include = 0; pos_to_include < n; pos_to_include++)
	{
		if (ops[pos_to_include].type == 0)
			continue;
		else
		{
			int number_to_include = ops[pos_to_include].argument;
			vector<vector<ll>> dp(n, vector<ll>(n));
			if (ops[0].type == 1)
			{
				if (ops[0].argument <= number_to_include)
				{
					dp[0][0] = 0;
					dp[0][1] = 1;
				}
				else
				{
					dp[0][0] = 1;
				}
			}
			else
			{
				dp[0][0] = 1;
			}
			for (int i = 1; i < n; i++)
			{
				dp[i] = dp[i - 1];
				if (ops[i].type == 0)
				{
					for (int j = 1; j < n; j++)
					{
						dp[i][j - 1] += dp[i - 1][j];
					}
				}
				else
				{
					if (ops[i].argument <= number_to_include)
					{
						for (int j = 1; j < n; j++)
						{
							dp[i][j] += dp[i-1][j-1];
							if (j == 1)
								dp[i][j]++;
						}
					}
					else
					{
						for (int j = 0; j < n; j++)
						{
							if (dp[i][j] > 0)
								dp[i][j]++;
						}
					}
				}
			}
			ll cnt = 0;
			for (int i = 1; i < n; i++)
			{
				cnt += dp.back()[i];
			}
			solution += cnt * number_to_include;
			solution %= mod;
		}
	}

	return 0;
}
