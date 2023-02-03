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
		int x; cin >> x;
		bool possible = 1;
		if (x & 1)
		{
			possible = 0;
		}
		for (int i = 1, mask = 2; i < 30 && possible; i++, mask <<= 1)
		{
			int prev_mask = (mask >> 1);
			if (x&mask && x&prev_mask)
				possible = 0;	
		}
		if (!possible)
		{
			cout << "-1\n";
			continue;
		}

		unsigned int a = 0, b = 0;
		x <<= 1;
		for (unsigned int i = 1, mask = 2; i <= 30 && possible; i++, mask <<= 1)
		{
			unsigned int prev_mask = (mask >> 1);
			unsigned int next_mask = (mask << 1);
			bool b0 = mask & x;
			bool b1 = prev_mask & x;
			bool b2 = next_mask & x;
			bool next_a = 0, next_b = 0;
			if (b0 == 0 && b1 == 0)
			{
				if (b2)
					next_a = 1, next_b = 1;
				else
					next_a = 0, next_b = 0;
			}
			else if (b0 == 0 && b1 == 1)
			{
				if (b2)
					next_a = 1, next_b = 1;
				else
					next_a = 0, next_b = 0;
			}
			else
			{
				next_a = 0, next_b = 1;
			}

			if (next_a)
				a |= prev_mask;
			if (next_b)
				b |= prev_mask;
		}
		cout << a << " " << b << endl;
	}

	return 0;
}