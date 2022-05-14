#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

pair<int,pair<int,int>> solve_nonzero(const vector<int>& elements)
{
	if (elements.empty())
	{
		return { 0,{0,0} };
	}
	int n = elements.size();
	vector<int> prefix_twos(n);
	prefix_twos[0] = (abs(elements[0]) == 2);
	for (int i = 1; i < n; i++)
	{
		prefix_twos[i] = prefix_twos[i - 1];
		if (elements[i] == 2 || elements[i] == -2)
			prefix_twos[i]++;
	}
	int rightmost_even = -1;
	int rightmost_odd = -1;
	int cnt_negative = 0;
	for (int i = 0; i < n; i++)
	{
		if (elements[i] < 0)
			cnt_negative++;
		if (cnt_negative % 2 == 0)
			rightmost_even = i;
		else
			rightmost_odd = i;
	}

	int best_score = 0;
	pair<int, int> best_sol = { n,0 };


	cnt_negative = 0;
	int j = -1;
	if (cnt_negative % 2 == 0)
		j = rightmost_even;
	else
		j = rightmost_odd;
	if (j >= 0)
	{
		int score = prefix_twos[j];
		if (score > best_score)
		{
			best_score = score;
			best_sol = { 0, n - j - 1 };
		}
	}

	for (int i = 0; i < n; i++)
	{
		if (elements[i] < 0)
			cnt_negative++;
		int j = -1;
		if (cnt_negative % 2 == 0)
			j = rightmost_even;
		else
			j = rightmost_odd;
		if (j >= i)
		{
			int score = prefix_twos[j] - prefix_twos[i];
			if (score > best_score)
			{
				best_score = score;
				best_sol = { i + 1, n - j - 1 };
			}
		}
	}
	return { best_score, best_sol };
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<int> current_vec;
		int cnt_front = 0;
		int best_score = 0;
		pair<int, int> best_sol = { n,0 };
		for (int i = 0; i < n; i++)
		{
			int x; cin >> x;
			if (x == 0)
			{
				int cnt_back = n - i;
				auto sol = solve_nonzero(current_vec);
				if (sol.first > best_score)
				{
					best_score = sol.first;
					int l = sol.second.first, r = sol.second.second;
					best_sol = { l + cnt_front, r + cnt_back };
				}
				cnt_front += current_vec.size() + 1;
				current_vec = vector<int>();
			}
			else
				current_vec.push_back(x);
		}
		int cnt_back = 0;
		auto sol = solve_nonzero(current_vec);
		if (sol.first > best_score)
		{
			best_score = sol.first;
			int l = sol.second.first, r = sol.second.second;
			best_sol = { l + cnt_front, r + cnt_back };
		}
		cout << best_sol.first << " " << best_sol.second << "\n";
	}

	return 0;
}