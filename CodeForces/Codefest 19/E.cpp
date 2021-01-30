#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <set>
using namespace std;
#define ll long long

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, num_cols;
	cin >> n >> num_cols;
	vector<ll> solution(num_cols);
	for (size_t i = 0; i < n; i++)
	{
		int length; cin >> length;
		int free_space = num_cols - length;
		vector<ll> row(length + 2 * free_space, 0);
		for (size_t i = free_space; i < free_space + length; i++)
			cin >> row[i];
		int l = 0, r = 0;
		deque<pair<ll, int>> reachable_elements;
		while (r <= free_space)
		{
			while (!reachable_elements.empty() && row[r] > reachable_elements.back().first)
				reachable_elements.pop_back();
			reachable_elements.push_back({ row[r++], r + free_space });
		}
		int row_index = 0;
		solution[row_index++] += reachable_elements.front().first;
		while (r < row.size())
		{
			while (!reachable_elements.empty() && reachable_elements.front().second == r)
			{
				reachable_elements.pop_front();
			}
			while (!reachable_elements.empty() && row[r] > reachable_elements.back().first)
				reachable_elements.pop_back();
			reachable_elements.push_back({ row[r++], r + free_space });
			solution[row_index++] += reachable_elements.front().first;
		}
	}

	for (ll col : solution)
		cout << col << " ";

	return 0;
}