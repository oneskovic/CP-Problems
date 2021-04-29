#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_count; cin >> test_count;
	for (size_t test_no = 0; test_no < test_count; test_no++)
	{
		int n; cin >> n;
		int upvote_cnt = 0;
		for (int i = 0; i < n; i++)
		{
			int type; cin >> type;
			if (type == 1 || type == 3)
			{
				upvote_cnt++;
			}
		}
		cout << upvote_cnt << "\n";
	}
	return 0;
}