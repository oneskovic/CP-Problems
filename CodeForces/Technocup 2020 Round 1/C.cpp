#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
typedef long long ll;

vector<ll> tickets;
ll a, b, percent_a, percent_b;
ll lcm_ab;

ll gcd(ll x, ll y)
{
	if (y == 0)
		return x;
	return gcd(y, x % y);
}

ll lcm(ll x, ll y)
{
	return (x * y) / gcd(x, y);
}

ll compute_score(int x)
{
	int n = tickets.size();
	ll both_a_and_b = x / lcm_ab;
	ll only_a = x / a - both_a_and_b;
	ll only_b = x / b - both_a_and_b;

	vector<ll> remaining = { both_a_and_b,only_a,only_b };
	vector<ll> multipliers = { percent_a+percent_b, percent_a, percent_b };
	if (percent_b > percent_a)
	{
		swap(remaining[1], remaining[2]);
		swap(multipliers[1], multipliers[2]);
	}

	ll score = 0;
	for (int i = 0; i < x; i++)
	{
		ll multiplier = 0;
		for (int j = 0; j < 3; j++)
		{
			if (remaining[j] > 0)
			{
				multiplier = multipliers[j];
				remaining[j]--;
				break;
			}
		}
		score += multiplier * tickets[i];
	}
	return score;
}

bool binary_search_comp(int x, ll searched_value)
{
	ll score = compute_score(x);
	return score < searched_value;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		ll n; cin >> n;
		tickets = vector<ll>(n);
		for (int i = 0; i < n; i++)
		{
			cin >> tickets[i];
			tickets[i] /= 100;
		}

		sort(tickets.begin(), tickets.end(), greater<ll>());

		cin >> percent_a >> a >> percent_b >> b;
		ll required_sum; cin >> required_sum;
		lcm_ab = lcm(a, b);

		if (compute_score(n) < required_sum)
		{
			cout << "-1\n";
			continue;
		}

		int l = 0, r = n;
		while (r-l > 1)
		{
			int mid = (l + r) / 2;
			if (compute_score(mid) >= required_sum)
			{
				r = mid;
			}
			else
				l = mid;
		}
		cout << r << "\n";
	}

	return 0;
}