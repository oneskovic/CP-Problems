#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

bool check_number(int number, vector<vector<pair<int, int>>>& scores)
{
	vector<int> number_count(scores[0].size());
	for (int row = 0; row < 5; row++)
	{
		for (int col = scores[0].size()-1; col > 0; col--)
		{
			if (scores[row][col].second == number)
			{
				break;
			}
			number_count[scores[row][col].second]++;
		}
	}
	for (int i = 0; i < scores[0].size(); i++)
	{
		if (i == number)
		{
			continue;
		}
		if (number_count[i] < 3)
		{
			return false;
		}
	}
	return true;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<vector<pair<int,int>>> scores(5, vector<pair<int,int>>(n));
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				cin >> scores[j][i].first;
				scores[j][i].second = i;
			}
		}
		for (int i = 0; i < 5; i++)
		{
			sort(scores[i].begin(), scores[i].end());
		}

		vector<int> count_on_right(n);

		int right_cnt = 0;
		for (int col = n-1; col >= 0; col--)
		{
			int to_add = 0;
			for (int row = 0; row < 5; row++)
			{
				int number = scores[row][col].second;
				count_on_right[number] += right_cnt;
			}
			right_cnt++;
		}
		bool f = false;
		for (int i = 0; i < n; i++)
		{
			if (count_on_right[i] >= 3*(n-1))
			{
				if (check_number(i, scores))
				{
					f = true;
					cout << i + 1 << "\n";
					break;
				}
			}
		}
		if (!f)
		{
			cout << "-1\n";
		}
	}

	return 0;
}