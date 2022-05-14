#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <limits.h>
#include <queue>
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
		vector<ll> elements(n);
		for (int i = 0; i < n; i++)
			cin >> elements[i];
		string colors; cin >> colors;
		vector<pair<ll, ll>> intervals; intervals.reserve(n);
		for (int i = 0; i < n; i++)
		{
			if (colors[i] == 'R')
				intervals.push_back({ elements[i],LLONG_MAX });
			else
				intervals.push_back({ LLONG_MIN, elements[i] });
		}
		sort(intervals.begin(), intervals.end());
		priority_queue<ll, vector<ll>, greater<ll>> current_right_borders;
		int i = 0;
		int goal_number = 1;
		bool possible = true;
		while(possible && goal_number <= n)
		{
			while (i < n && intervals[i].first <= goal_number)
			{
				current_right_borders.push(intervals[i++].second);
			}
			while (!current_right_borders.empty() && current_right_borders.top() < goal_number)
			{
				current_right_borders.pop();
			}
			if (current_right_borders.empty())
			{
				possible = false;
			}
			else
			{
				current_right_borders.pop();
				goal_number++;
			}
		}
		if (possible)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}