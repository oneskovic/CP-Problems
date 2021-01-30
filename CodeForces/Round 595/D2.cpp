#include <iostream>
#include <algorithm>
#include <deque>
#include <set>
#include <vector>
using namespace std;

struct segment
{
	int left_point, right_point;
	int index;
};

bool operator> (const segment& lhs, const segment& rhs)
{
	return lhs.right_point > rhs.right_point;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, max_segments;
	cin >> n >> max_segments;
	vector<segment> segments = vector<segment>(n);
	for (size_t i = 0; i < n; i++)
	{
		cin >> segments[i].left_point >> segments[i].right_point;
		segments[i].index = i+1;
	}
	sort(segments.begin(), segments.end(), [](const segment& lhs, const segment& rhs) 
		{
			return lhs.left_point < rhs.left_point; 
		});
	int current_point_segments = 0;
	vector<int> segments_to_remove;
	int segments_it = 0;
	multiset<segment,greater<segment>> previous_segments;
	for (int current_x = segments.front().left_point; current_x <= segments.back().right_point; current_x++)
	{
		while (!previous_segments.empty() && (--previous_segments.end())->right_point < current_x)
			previous_segments.erase(--previous_segments.end());

		while (segments_it < segments.size() && segments[segments_it].left_point <= current_x)
		{
			previous_segments.insert(segments[segments_it]);
			segments_it++;
		}

		while (previous_segments.size() > max_segments)
		{
			segments_to_remove.push_back(previous_segments.begin()->index);
			previous_segments.erase(previous_segments.begin());
		}
	}

	cout << segments_to_remove.size() << "\n";
	for (int index : segments_to_remove)
		cout << index << " ";
	cout << "\n";
	return 0;
}