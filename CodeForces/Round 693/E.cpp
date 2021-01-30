#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

struct rectangle
{
	int height, width, index;
};
struct compare_rect_heights
{
	inline bool operator() (const rectangle& lhs, const rectangle& rhs) const
	{
		return lhs.height < rhs.height;
	}
};
struct compare_rect_widths
{
	inline bool operator() (const rectangle& lhs, const rectangle& rhs) const
	{
		return lhs.width < rhs.width;
	}
};

int get_smaller_width_index(rectangle rect, set<rectangle, compare_rect_widths>& smaller_height)
{
	if (smaller_height.empty() || smaller_height.begin()->width >= rect.width)
	{
		return -2;
	}
	else
	{
		if (smaller_height.begin()->index == rect.index)
		{
			if (smaller_height.size() <= 1 || (++smaller_height.begin())->width >= rect.width)
				return -2;
			else
				return (++smaller_height.begin())->index;
		}
		else
		{
			return smaller_height.begin()->index;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		vector<rectangle> rectangles;
		for (int i = 0; i < n; i++)
		{
			int h, w;
			cin >> h >> w;
			rectangles.push_back({ h,w,i });
			rectangles.push_back({ w,h,i });
		}
		sort(rectangles.begin(), rectangles.end(), compare_rect_heights());

		vector<int> solution(n);
		set<rectangle, compare_rect_widths> smaller_height, equal_height;
		equal_height.insert(rectangles[0]);
		for (size_t i = 1; i < rectangles.size(); i++)
		{
			if (rectangles[i].height > rectangles[i-1].height)
			{
				for (auto r: equal_height)
					smaller_height.insert(r);
				equal_height.clear();
			}
			int smaller_index = get_smaller_width_index(rectangles[i], smaller_height);
			solution[rectangles[i].index] = smaller_index;
			equal_height.insert(rectangles[i]);
		}

		for (size_t i = 0; i < n; i++)
			cout << solution[i]+1 << " ";
		cout << "\n";
	}
	return 0;
}