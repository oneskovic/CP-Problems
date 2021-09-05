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
	while (test_cnt--)
	{
		ll k; cin >> k;
		ll root_k = 1;
		while (root_k * root_k < k)
			root_k++;
		if (root_k * root_k >= k)
		{
			root_k--;
		}
		ll start_number = root_k * root_k + 1;
		ll end_number = (root_k + 1) * (root_k + 1);
		ll dist = k - start_number;
		ll col = -1, row = -1;
		if (dist <= root_k)
		{
			col = root_k + 1;
			row = k - start_number + 1;
		}
		else
		{
			row = root_k + 1;
			col = end_number - k + 1;
		}
		cout << row << " " << col << "\n";
	}

	return 0;
}