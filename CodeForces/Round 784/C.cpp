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
		int n; cin >> n;
		vector<int> elements(n);
		vector<int> odd(2);
		vector<int> even(2);
		for (int i = 0; i < n; i++)
		{
			cin >> elements[i];
			if (elements[i] & 1)
				odd[i & 1]++;
			else
				even[i & 1]++;
		}
		if (odd[0] * even[0] == 0 && odd[1] * even[1] == 0)
			cout << "yes\n";
		else
			cout << "no\n";
	}

	return 0;
}
