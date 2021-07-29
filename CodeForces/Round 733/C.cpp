#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

ll div_4_floor(ll x)
{
	if (x % 4 == 0)
	{
		return x / 4;
	}
	else
	{
		return (x - x % 4) / 4;
	}
}

ll choose_optimally(const vector<ll>& prefix_sums, ll round_number)
{
	ll score = 0;
	ll start_round_cnt = prefix_sums.size();
	ll to_choose = round_number - div_4_floor(round_number);
	ll to_choose_from_scores = max((ll)0, to_choose - (round_number - start_round_cnt));
	if (to_choose_from_scores > 0)
	{
		score = prefix_sums[to_choose_from_scores - 1];
	}
	score += (to_choose - to_choose_from_scores) * 100;
	return score;
}

bool f(ll round_number, const vector<ll>& prefix_sums1, const vector<ll>& prefix_sums2)
{
	ll score1 = choose_optimally(prefix_sums1, round_number);

	ll to_choose = min((ll)prefix_sums2.size(), round_number - div_4_floor(round_number));
	ll score2 = prefix_sums2[to_choose-1];
	return score1 >= score2;
}

ll binary_search(const vector<int>& scores1, const vector<int>& scores2)
{
	vector<ll> prefix_sums1(scores1.size()), prefix_sums2(scores2.size());
	prefix_sums1[0] = scores1[0];
	for (int i = 1; i < scores1.size(); i++)
	{
		prefix_sums1[i] = prefix_sums1[i - 1] + scores1[i];
	}
	prefix_sums2[0] = scores2[0];
	for (int i = 1; i < scores2.size(); i++)
	{
		prefix_sums2[i] = prefix_sums2[i - 1] + scores2[i];
	}

	ll l = scores1.size(), r = 1e8;
	while (r-l>1)
	{
		ll mid = (l + r) / 2;
		if (f(mid,prefix_sums1,prefix_sums2))
		{
			r = mid;
		}
		else
		{
			l = mid;
		}
	}
	return r;
}

ll solve(vector<int> scores1, vector<int> scores2)
{
	sort(scores1.begin(), scores1.end(), greater<int>());
	sort(scores2.begin(), scores2.end(), greater<int>());
	int n = scores1.size();
	int to_choose = n - div_4_floor(n);
	ll sum1 = 0, sum2 = 0;
	for (int i = 0; i < to_choose; i++)
	{
		sum1 += scores1[i];
		sum2 += scores2[i];
	}
	if (sum2 <= sum1)
	{
		return 0;
	}
	ll solution = binary_search(scores1, scores2);
	return solution - n;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<int> scores1(n), scores2(n);
		for (int i = 0; i < n; i++)
			cin >> scores1[i];
		for (int i = 0; i < n; i++)
			cin >> scores2[i];
		cout << solve(scores1, scores2) << "\n";
	}
	return 0;
}