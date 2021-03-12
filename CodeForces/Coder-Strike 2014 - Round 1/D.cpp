#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m; cin >> n >> m;
	vector<unordered_set<int>> cant_appear_before (n+1);

	for (size_t i = 0; i < m; i++)
	{
		int a, b; cin >> a >> b;
		cant_appear_before[b].insert(a);
	}

	vector<int> solution;
	solution.reserve(n);
	for (int i = 1; i <= n; i++)
	{
		solution.push_back(i);
		int position = solution.size() - 1;
		while (position > 0 && cant_appear_before[i].find(solution[position - 1]) != cant_appear_before[i].end())
		{
			swap(solution[position - 1], solution[position]);
			position--;
		}
	}

	for (int i: solution)
	{
		cout << i << " ";
	}

	return 0;
}