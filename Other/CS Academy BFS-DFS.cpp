#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n; cin >> n;
	vector<int> dfs_order(n), bfs_order(n);
	for (int i = 0; i < n; i++)
		cin >> bfs_order[i];
	for (int i = 0; i < n; i++)
		cin >> dfs_order[i];
	if (n == 1)
	{
		cout << 0 << endl;
		return 0;
	}
	if (dfs_order[1] != bfs_order[1])
	{
		cout << -1 << endl;
		return 0;
	}
	cout << 2*(n-1) - 1 << endl;
	for (int i = 1; i < n; i++)
		cout << bfs_order[0] << " " << bfs_order[i] << endl;
	for (int i = 1; i < n-1; i++)
		cout << dfs_order[i] << " " << dfs_order[i + 1] << endl;
	
	return 0;
}