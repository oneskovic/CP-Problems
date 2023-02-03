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
		int n, s1, s2;
		cin >> n >> s1 >> s2;
		int max = s1 - s2;
		s1 -= n;
		while (s1 - (max-1) >= 0 && s1 > 0)
		{
			cout << max << " ";
			s1 -= max-1;
			n--;
		}
		if (s1 > 0)
		{
			cout << s1+1 << " ";
			n--;
		}
		while (n > 0)
		{
			cout << 1 << " ";
			n--;
		}
		cout << endl;
	}

	return 0;
}