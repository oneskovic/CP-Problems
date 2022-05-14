#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		string s; cin >> s;
		int n = s.size();
		vector<int> prefix_a(n), prefix_b(n), suffix_b(n);
		prefix_a[0] = (s[0] == 'A');
		prefix_b[0] = (s[0] == 'B');
		suffix_b.back() = (s.back() == 'B');
		for (int i = 1; i < n; i++)
		{
			prefix_a[i] = prefix_a[i - 1] + (s[i] == 'A');
			prefix_b[i] = prefix_b[i - 1] + (s[i] == 'B');
		}
		for (int i = n - 2; i >= 0; i--)
			suffix_b[i] = suffix_b[i + 1] + (s[i] == 'B');
		
		bool ok = 1;
		for (int i = 0; i < n && ok; i++)
		{
			if (s[i] == 'B' && prefix_a[i] < prefix_b[i])
				ok = 0;
			else if (s[i] == 'A' && suffix_b[i] < 1)
				ok = 0;
		}
		if (ok)
			cout << "yes\n";
		else
			cout << "no\n";

	}

	return 0;
}