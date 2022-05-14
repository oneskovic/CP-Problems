#include <algorithm>
#include <iostream>
#include <limits.h>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;
typedef long long ll;

struct point
{
	int x, y, cnt;
};

int compute_distance(const point& p1, const point& p2)
{
	return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

struct pq_element
{
	int distance, x, y, index;
};
bool operator > (const pq_element& lhs, const pq_element& rhs)
{
	tuple<int, int, int> tlhs = { lhs.distance, lhs.x, lhs.y };
	tuple<int, int, int> trhs = { rhs.distance, rhs.x, rhs.y };
	return tlhs > trhs;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n, m; cin >> n >> m;
		vector<point> points(m);
		for (int i = 0; i < m; i++)
			cin >> points[i].x >> points[i].y >> points[i].cnt;
		
		vector<priority_queue<pq_element, vector<pq_element>, greater<pq_element>>> queues(m);
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (i != j)
				{
					queues[i].push({ compute_distance(points[i],points[j]),points[j].x,points[j].y,j });
				}
			}
		}
		
		int cnt_nonzero = m;
		int current_node = 0;
		int prev_node = -1;
		ll solution = 0;
		points[current_node].cnt--;
		while (cnt_nonzero > 1)
		{
			int next_node = -1;
			if (queues[current_node].size() == 1)
			{
				next_node = queues[current_node].top().index;
				if (points[next_node].cnt == 0)
				{
					queues[current_node].pop();
					continue;
				}
				solution += queues[current_node].top().distance;
				points[next_node].cnt--;
				if (points[next_node].cnt == 0)
				{
					queues[current_node].pop();
					cnt_nonzero--;
				}
			}
			else
			{
				next_node = queues[current_node].top().index;
				bool need_to_return = false;
				pq_element temp;
				if (next_node == prev_node)
				{
					need_to_return = true;
					temp = queues[current_node].top();
					queues[current_node].pop();
					next_node = queues[current_node].top().index;
				}
				if (points[next_node].cnt == 0)
				{
					queues[current_node].pop();
					if (need_to_return)
						queues[current_node].push(temp);
					continue;
				}
				solution += queues[current_node].top().distance;
				points[next_node].cnt--;
				if (points[next_node].cnt == 0)
				{
					queues[current_node].pop();
					cnt_nonzero--;
				}
				if (need_to_return)
					queues[current_node].push(temp);
			}
			prev_node = current_node;
			current_node = next_node;
		}
		cout << solution;
	}

	return 0;
}