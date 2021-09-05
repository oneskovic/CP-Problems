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
	int maxn = 3 * 1e5 + 1;
	vector<int> prefix_xor(maxn+1);
	for (int i = 1; i <= maxn; i++)
		prefix_xor[i] = prefix_xor[i - 1] ^ i;
	
	while (test_cnt--)
	{
		int minimum_excluded, target_xor;
		cin >> minimum_excluded >> target_xor;
		if (prefix_xor[minimum_excluded-1] == target_xor)
		{
			cout << minimum_excluded << "\n";
		}
		else
		{
			int value_to_add = prefix_xor[minimum_excluded - 1] ^ target_xor;
			if (value_to_add == minimum_excluded)
			{
				cout << minimum_excluded + 2 << "\n";
			}
			else
				cout << minimum_excluded + 1 << "\n";
		}
	}
	return 0;
}