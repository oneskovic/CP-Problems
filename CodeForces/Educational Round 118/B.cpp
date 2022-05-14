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
		vector<ll> elements(n);
		for (int i = 0; i < n; i++)
			cin >> elements[i];
		sort(elements.begin(), elements.end());
		for (int i = 0; i < n/2; i++)
		{
			cout << elements[i+1] << " " << elements[0] << "\n";
		}

	}

	return 0;
}