#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void solve(vector<int>& colors, vector<int>& desired_colors, vector<int>& painters)
{
	int n = colors.size();
	int m = painters.size();
	vector<vector<int>> color_position_map(n + 1, vector<int>());
	for (size_t i = 0; i < n; i++)
	{
		if (colors[i] != desired_colors[i])
		{
			color_position_map[desired_colors[i]].push_back(i);
		}
	}
	int last_painter_color = painters.back();
	int last_plank_index = -1;
	if (color_position_map[last_painter_color].empty())
	{
		for (int i = n - 1; i >= 0; i--)
		{
			if (desired_colors[i] == last_painter_color)
			{
				last_plank_index = i;
				break;
			}
		}
	}
	else
	{
		last_plank_index = color_position_map[last_painter_color].back();
	}

	if (last_plank_index == -1)
	{
		cout << "no\n";
	}
	else
	{
		bool need_to_repaint_last_plank = false;
		if (!color_position_map[last_painter_color].empty() && color_position_map[last_painter_color].back() == last_plank_index)
		{
			color_position_map[last_painter_color].pop_back();
			need_to_repaint_last_plank = true;
		}
		vector<int> solution(m);
		for (size_t i = 0; i < m - 1; i++)
		{
			int current_color = painters[i];
			if (color_position_map[current_color].empty())
			{
				solution[i] = last_plank_index;
				need_to_repaint_last_plank = true;
			}
			else
			{
				solution[i] = color_position_map[current_color].back();
				color_position_map[current_color].pop_back();
			}
		}
		if (need_to_repaint_last_plank || color_position_map[last_painter_color].empty())
		{
			solution[m - 1] = last_plank_index;
		}
		else
		{
			solution[m - 1] = color_position_map[last_painter_color].back();
			color_position_map[last_painter_color].pop_back();
		}

		bool correct = true;
		for (size_t i = 0; i < color_position_map.size(); i++)
		{
			if (!color_position_map[i].empty())
			{
				correct = false;
				break;
			}
		}
		if (correct)
		{
			cout << "yes\n";
			for (int i : solution)
				cout << i + 1 << " ";
			cout << "\n";
		}
		else
		{
			cout << "no\n";
		}
	}
}

vector<int> rand_vec(int n, int min_val = 1, int max_val = 5)
{
	vector<int> r(n);
	for (size_t i = 0; i < n; i++)
	{
		r[i] = min_val + (rand() % (max_val - min_val + 1));
	}
	return r;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n, m; cin >> n >> m;
		vector<int> colors(n), desired_colors(n), painters(m);
		for (size_t i = 0; i < n; i++)
			cin>> colors[i];
		for (size_t i = 0; i < n; i++)
			cin >> desired_colors[i];
		for (size_t i = 0; i < m; i++)
			cin >> painters[i];
		solve(colors, desired_colors, painters);
	}
	return 0;
}