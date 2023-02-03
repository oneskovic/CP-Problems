#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;

struct interval_point
{
	int time;
	bool is_start;
	int index;
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<interval_point> interval_points; interval_points.reserve(2 * n);
	for (int i = 0; i < n; i++)
	{
		int start_time, end_time; cin >> start_time >> end_time;
		interval_points.push_back({ start_time, 1, i });
		interval_points.push_back({ end_time, 0, i });
	}
	sort(interval_points.begin(), interval_points.end(), 
		[](const interval_point& lhs, const interval_point& rhs) {
			return lhs.time < rhs.time;
		});

	vector<bool> is_done(n);
	vector<int> solution(n);
	set<pair<int, int>> active_intervals; // Set of: (start time, interval index)
	
	for (const auto& point: interval_points)
	{
		if (point.is_start)
			active_intervals.insert({ point.time, point.index });
		else
		{
			is_done[point.index] = 1;
			while (!active_intervals.empty() && is_done[active_intervals.begin()->second])
			{
				solution[active_intervals.begin()->second] = point.time;
				active_intervals.erase(active_intervals.begin());
			}
		}
	}
	for (int end_time: solution)
		cout << end_time << "\n";
	

	return 0;
}