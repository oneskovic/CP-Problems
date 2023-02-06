#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	map<ll, int> segment_parts;
	for (int i = 0; i < n; i++)
	{
		ll l, r; cin >> l >> r;
		segment_parts[l]++;
		segment_parts[r+1]--;
	}

	map<int, ll> covered_by_cnt;
	int current_cnt = segment_parts.begin()->second;
	ll prev_pos = segment_parts.begin()->first;
	for (auto it = ++segment_parts.begin(); it != segment_parts.end(); it++)
	{
		ll current_pos = it->first;
		covered_by_cnt[current_cnt] += current_pos - prev_pos;
		prev_pos = current_pos;
		current_cnt += it->second;
	}
	for (int i = 1; i <= n; i++)
		cout << covered_by_cnt[i] << " ";
	

	return 0;
}