#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
using namespace std;
typedef long long ll;

int bruteforce(int sum_a, int sum_b, const vector<int>& elements, int pos = 0)
{
	if (pos == elements.size())
		return abs(sum_a) - abs(sum_b);
	
	int s1 = bruteforce(sum_a + elements[pos], sum_b, elements, pos + 1);
	int s2 = bruteforce(sum_a, sum_b + elements[pos], elements, pos + 1);
	return max(s1, s2);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int test_cnt; cin >> test_cnt;
	while (test_cnt--)
	{
		int n; cin >> n;
		if (n % 2 == 0)
		{
			cout << n / 2 << "\n";
			int l = 0, r = 3*n - 2;
			for (int i = 0; i < n/2; i++)
			{
				cout << l+1 << " " << r+1 << "\n";
				l += 3;
				r -= 3;
			}
		}
		else
		{
			cout << n / 2 + 1 << "\n";
			int l = 0, r = 3*n - 2;
			for (int i = 0; i < n / 2 + 1; i++)
			{
				cout << l + 1 << " " << r + 1 << "\n";
				l += 3;
				r -= 3;
			}

		}
	}

	return 0;
}