#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

bool check_pos(int i, const vector<ll>& a, const vector<ll>& b)
{
	return a[i] <= b[i - 1];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		vector<ll> elements_a(n), elements_b(n);
		for (int i = 0; i < n; i++)
			cin >> elements_a[i];
		for (int i = 0; i < n; i++)
			cin >> elements_b[i];

		for (int i = 0; i < n; i++)
			cout << *lower_bound(elements_b.begin(), elements_b.end(), elements_a[i]) - elements_a[i] << " ";
		cout << "\n";
		int l = 0, r = 1;
		while (l < n)
		{
			while (r < n && check_pos(r, elements_a, elements_b))
				r++;
			cout << elements_b[r - 1] - elements_a[l] << " ";
			l++;
			r = max(l+1, r);
		}
		cout << "\n";

	}

	return 0;
}