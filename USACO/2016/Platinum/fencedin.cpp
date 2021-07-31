#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;


int main()
{
	freopen("fencedin.in", "r", stdin);
	freopen("fencedin.out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(0);

	ll end_x, end_y; int vertical_cnt, horizontal_cnt;
	cin >> end_x >> end_y >> vertical_cnt >> horizontal_cnt;
	vector<ll> vertical_lines(vertical_cnt), horizontal_lines(horizontal_cnt);
	for (int i = 0; i < vertical_cnt; i++)
		cin >> vertical_lines[i];
	for (int i = 0; i < horizontal_cnt; i++)
		cin >> horizontal_lines[i];
	
	vertical_lines.push_back(0);
	vertical_lines.push_back(end_x);
	horizontal_lines.push_back(0);
	horizontal_lines.push_back(end_y);

	sort(vertical_lines.begin(), vertical_lines.end());
	sort(horizontal_lines.begin(), horizontal_lines.end());
	vector<ll> row_cost, col_cost;
	for (int i = 1; i < vertical_lines.size(); i++)
	{
		ll cost = vertical_lines[i] - vertical_lines[i - 1];
		col_cost.push_back(cost);
	}
	for (int i = 1; i < horizontal_lines.size(); i++)
	{
		ll cost = horizontal_lines[i] - horizontal_lines[i - 1];
		row_cost.push_back(cost);
	}
	sort(row_cost.begin(), row_cost.end());
	sort(col_cost.begin(), col_cost.end());
	
	ll total_cost = row_cost.front()*vertical_cnt + col_cost.front()*horizontal_cnt;
	vertical_cnt++; horizontal_cnt++;
	for (int i = 1, j = 1; i < row_cost.size() && j < col_cost.size();)
	{
		if (row_cost[i] < col_cost[j])
		{
			int cnt = vertical_cnt - j;
			total_cost += row_cost[i] * cnt;
			i++;
		}
		else
		{
			int cnt = horizontal_cnt - i;
			total_cost += col_cost[j] * cnt;
			j++;
		}
	}
	cout << total_cost << "\n";
	return 0;
}