#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>
#include <limits.h>
using namespace std;
typedef long long ll;

struct mountain
{
	ll x, left_point, right_point;
};
bool operator<(const mountain& lhs, const mountain& rhs)
{
	return lhs.x < rhs.x;
}

int solve(const vector<mountain>& mountains)
{
	int n = mountains.size();
	
	vector<ll> suffix_min(n);
	suffix_min[n - 1] = LLONG_MAX;
	for (int i = n-2; i >= 0; i--)
		suffix_min[i] = min(suffix_min[i + 1], mountains[i + 1].left_point);

	vector<ll> prefix_max(n);
	prefix_max[0] = LLONG_MIN;
	for (int i = 1; i < n; i++)
		prefix_max[i] = max(prefix_max[i - 1], mountains[i - 1].right_point);

	int solution = 0;
	for (int i = 0; i < n; i++)
		if (suffix_min[i] > mountains[i].left_point &&
			prefix_max[i] < mountains[i].right_point)
			solution++;
	return solution;
}

int main()
{
	freopen("mountains.in", "r", stdin);
	freopen("mountains.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<mountain> mountains(n);
	for (int i = 0; i < n; i++)
	{
		ll x, height;
		cin >> x >> height;
		ll left_point = x - height, right_point = x + height;
		mountains[i] = { x, left_point, right_point };
	}
	sort(mountains.begin(), mountains.end());

	cout << solve(mountains) << "\n";

	return 0;
}