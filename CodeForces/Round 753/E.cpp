#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		ll max_w, max_h; cin >> max_h >> max_w;
		string commands; cin >> commands;
		ll min_x = 0, max_x = 0;
		ll min_y = 0, max_y = 0;
		ll current_x = 0, current_y = 0;
		ll solution = 0;
		for (int i = 0; i < commands.size(); i++)
		{
			switch (commands[i])
			{
			case 'L':
				current_x--;
				break;
			case 'R':
				current_x++;
				break;
			case 'U':
				current_y++;
				break;
			case 'D':
				current_y--;
				break;
			}
			vector<ll> temp = { min_x, max_x, min_y, max_y };
			min_x = min(min_x, current_x);
			max_x = max(max_x, current_x);
			min_y = min(min_y, current_y);
			max_y = max(max_y, current_y);
			if (max_x - min_x >= max_w || max_y - min_y >= max_h)
			{
				min_x = temp[0];
				max_x = temp[1];
				min_y = temp[2];
				max_y = temp[3];
				solution = i;
				break;
			}
		}
		cout << max_h + min_y << " " << 1 + abs(min_x) << "\n";
	}

	return 0;
}