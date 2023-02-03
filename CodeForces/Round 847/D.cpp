#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		multiset<int> s;
		for (int i = 0; i < n; i++)
		{
			int x; cin >> x;
			s.insert(x);
		}
		int sol = 0;
		while (!s.empty())
		{
			sol++;
			int current_num = *s.begin();
			do
			{
				s.erase(s.find(current_num));
				current_num++;
			} while (s.find(current_num) != s.end());
		}
		cout << sol << endl;
	}

	return 0;
}