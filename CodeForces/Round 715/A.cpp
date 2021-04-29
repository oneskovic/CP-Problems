#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int test_cnt; cin >> test_cnt;
	for (size_t test_no = 0; test_no < test_cnt; test_no++)
	{
		int n; cin >> n;
		vector<pair<int, int>> elements(n);
		for (int i = 0; i < n; i++)
		{
			int a; cin >> a;
			elements[i] = { a % 2,a };
		}
		sort(elements.begin(), elements.end());
		for (size_t i = 0; i < n; i++)
		{
			cout << elements[i].second << " ";
		}
		cout << "\n";
	}
	return 0;
}