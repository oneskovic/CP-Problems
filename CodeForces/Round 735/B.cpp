#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;
typedef long long ll;

ll solve(const vector<ll>& elements, int k)
{
	int n = elements.size();
	ll max_score = LLONG_MIN;
	for (ll i = n; i > 0; i--)
	{
		ll left_bound = 1, j = i - 1;
		while (j >= left_bound)
		{
			ll current_score = (i * j) - k * (elements[i-1] | elements[j-1]);
			// (i*x) - k*(elements[i]) < current_score
			// i*x < current_score + k*elements[i]
			// x < (current_score + k*elements[i])/i
			left_bound = max(left_bound, (current_score + k * elements[i-1]) / i);
			j--;
			max_score = max(max_score, current_score);
		}
	}
	return max_score;
}
ll brutus(const vector<ll>& v, int k)
{
	ll max_score = LLONG_MIN;
	for (ll i = 0; i < v.size(); i++)
	{
		for (ll j = i+1; j < v.size(); j++)
		{
			ll current_score = ((i+1) * (j+1)) - k * (v[i] | v[j]);
			max_score = max(max_score, current_score);
		}
	}
	return max_score;
}

vector<ll> rand_vec(int n)
{
	vector<ll> v(n);
	for (int i = 0; i < n; i++)
	{
		v[i] = rand() % 100000;
	}
	return v;
}

int main()
{
	//srand(time(0));
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n, k; cin >> n >> k;
		vector<ll> elements(n);
		for (int i = 0; i < n; i++)
			cin >> elements[i];
	
		cout << solve(elements,k) << "\n";
	}

	return 0;
}