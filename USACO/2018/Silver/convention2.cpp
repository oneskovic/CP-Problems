#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;
typedef long long ll;

struct cow
{
	int arrival_time, time, priority;
};

bool operator <(const cow& lhs, const cow& rhs)
{
	return lhs.arrival_time < rhs.arrival_time;
}

int main()
{
	freopen("convention2.in", "r", stdin);
	freopen("convention2.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<cow> cows(n);
	for (int i = 0; i < n; i++)
	{
		cin >> cows[i].arrival_time >> cows[i].time;
		cows[i].priority = n-i;
	}
	
	sort(cows.begin(), cows.end());
	priority_queue<pair<int, int>> queue;
	queue.push({ cows[0].priority,0 });
	int current_pos = 1;
	int current_time = cows[0].arrival_time;
	while (current_pos < n && cows[current_pos].arrival_time <= current_time)
	{
		queue.push({ cows[current_pos].priority,current_pos });
		current_pos++;
	}
	int max_wait = 0;
	while (!queue.empty())
	{
		int current_cow_index = queue.top().second;
		queue.pop();
		int wait_time = current_time - cows[current_cow_index].arrival_time;
		max_wait = max(max_wait, wait_time);
		current_time += cows[current_cow_index].time;
		while (current_pos < n && cows[current_pos].arrival_time <= current_time)
		{
			queue.push({ cows[current_pos].priority,current_pos });
			current_pos++;
		}
		if (queue.empty() && current_pos < n)
			current_time = cows[current_pos].arrival_time;
		while (current_pos < n && cows[current_pos].arrival_time <= current_time)
		{
			queue.push({ cows[current_pos].priority,current_pos });
			current_pos++;
		}
	}
	cout << max_wait;

	return 0;
}